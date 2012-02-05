/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "ox820_gmac.h"
#include <linux/moduleparam.h>

#define CARDNAME "ox820-gmac"

/* Ethernet MAC adr to assign to interface */
static int mac_addrs[2][6] = { { 0x00, 0x30, 0xe0, 0x00, 0x00, 0x00 },
			  { 0x00, 0x30, 0xe0, 0x00, 0x00, 0x01 } };
module_param_array_named(mac_adr,   mac_addrs[0], int, NULL, S_IRUGO);
module_param_array_named(mac_2_adr, mac_addrs[1], int, NULL, S_IRUGO);

static struct ox820_sysctrl_registers_t* const sysctrl = (struct ox820_sysctrl_registers_t*) SYS_CONTROL_BASE;

/*=============================================================================*/
static int ox820_gmac_drv_probe(struct platform_device *pdev)
{
	struct net_device *ndev;
	struct ox820_gmac_t* gmac;
	int ret;
	struct resource* memres = platform_get_resource(pdev, IORESOURCE_MEM, 0 );
	int irq = platform_get_irq(pdev, 0);
	/* platform_data contains control information for whether use leon and so on */
	struct ox820_gmac_platform_data_t* pdata = (struct ox820_gmac_platform_data_t *)pdev->dev.platform_data;

	ndev = alloc_etherdev(sizeof (struct ox820_gmac_t));
	if (!ndev) {
		printk("%s: could not allocate device.\n", CARDNAME);
		ret = -ENOMEM;
		goto exit;
	}
	SET_NETDEV_DEV(ndev, &pdev->dev);

	platform_set_drvdata(pdev, ndev);

	gmac = netdev_priv(ndev);

	/* initialize our private data */
	memset(gmac, 0, sizeof(struct ox820_gmac_t));
	gmac->gmac_unit = pdev->id;
	gmac->phy_adr = pdata->phy_adr;
	spin_lock_init(&gmac->dma.tx_free_descriptors_spinlock);
	spin_lock_init(&gmac->dma.tx_schedule_descriptors_spinlock);

	if (!request_mem_region(memres->start, resource_size(memres),
				"ox820-gmac")) {
		dev_dbg(&pdev->dev, "controller already in use\n");
		ret = -EBUSY;
		goto exit_free_netdev;
	}

	gmac->gmac_regs = ioremap(memres->start, resource_size(memres));
	if (NULL == gmac->gmac_regs) {
		dev_dbg(&pdev->dev, "error mapping memory\n");
		ret = -EFAULT;
		goto exit_release_mem_region;
	}


	ndev->irq = irq;

	/* Initialize GMAC */
	ox820_gmac_initialize_regs(gmac);

	ox820_gmac_set_mac_address(ndev, mac_addrs[gmac->gmac_unit]);

	ret = ox820_gmac_plain_init(ndev, gmac);
	if(0 != ret) {
		goto exit_iounmap;
	}

	ret = request_irq(ndev->irq, ox820_gmac_irq_handler, 0, "ox820-gmac", gmac);
	if(0 != ret) {
		goto exit_gmac_dma_cleanup;
	}

	return 0;

exit_gmac_dma_cleanup:
	/* stop GMAC since we take away the DMA descriptors */
	switch(gmac->gmac_unit) {
		case 0:
			sysctrl->rsten_set_ctrl = MSK_OX820_SYSCTRL_RSTEN_ETHA;
			sysctrl->cken_clr_ctrl = MSK_OX820_SYSCTRL_CKEN_ETHA;
			break;
		case 1:
			sysctrl->rsten_set_ctrl = MSK_OX820_SYSCTRL_RSTEN_ETHB;
			sysctrl->cken_clr_ctrl = MSK_OX820_SYSCTRL_CKEN_ETHB;
			break;
	}
	wmb();
	ox820_gmac_dma_cleanup(gmac);
exit_iounmap:
	iounmap(gmac->gmac_regs);
exit_release_mem_region:
	release_mem_region(memres->start, resource_size(memres));
exit_free_netdev:
	/* stop GMAC */
	switch(gmac->gmac_unit) {
		case 0:
			sysctrl->rsten_set_ctrl = MSK_OX820_SYSCTRL_RSTEN_ETHA;
			sysctrl->cken_clr_ctrl = MSK_OX820_SYSCTRL_CKEN_ETHA;
			break;
		case 1:
			sysctrl->rsten_set_ctrl = MSK_OX820_SYSCTRL_RSTEN_ETHB;
			sysctrl->cken_clr_ctrl = MSK_OX820_SYSCTRL_CKEN_ETHB;
			break;
	}
	wmb();

	platform_set_drvdata(pdev, NULL);
	free_netdev(ndev);
exit:
	return ret;
}


/*=============================================================================*/
static int ox820_gmac_drv_remove(struct platform_device *pdev)
{
	struct net_device *ndev = dev_get_drvdata(&pdev->dev);
	struct ox820_gmac_t *gmac = netdev_priv(ndev);
	struct resource* memres = platform_get_resource(pdev, IORESOURCE_MEM, 0 );

	platform_set_drvdata(pdev, NULL);

	unregister_netdev(ndev);

	free_irq(ndev->irq, pdev);
	/* stop GMAC */
	switch(gmac->gmac_unit) {
		case 0:
			sysctrl->rsten_set_ctrl = MSK_OX820_SYSCTRL_RSTEN_ETHA;
			sysctrl->cken_clr_ctrl = MSK_OX820_SYSCTRL_CKEN_ETHA;
			break;
		case 1:
			sysctrl->rsten_set_ctrl = MSK_OX820_SYSCTRL_RSTEN_ETHB;
			sysctrl->cken_clr_ctrl = MSK_OX820_SYSCTRL_CKEN_ETHB;
			break;
	}

	ox820_gmac_dma_cleanup(gmac);
	iounmap(gmac->gmac_regs);
	release_mem_region(memres->start, resource_size(memres));
	free_netdev(ndev);

	return 0;
}

/*=============================================================================*/
static struct platform_driver ox820_gmac_driver = {
	.probe		= ox820_gmac_drv_probe,
	.remove		= ox820_gmac_drv_remove,
	.driver		= {
		.name	= CARDNAME,
		.owner	= THIS_MODULE,
	},
};

/*=============================================================================*/
static int __init ox820_gmac_init(void) {
	return platform_driver_register(&ox820_gmac_driver);
}

/*=============================================================================*/
static void __exit ox820_gmac_cleanup(void) {
	platform_driver_unregister(&ox820_gmac_driver);
}

/*=============================================================================*/
module_init(ox820_gmac_init);
module_exit(ox820_gmac_cleanup);


MODULE_DESCRIPTION("ox820_gmac Network Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION("v2.0");
MODULE_ALIAS("platform:" CARDNAME);
