/*
 * drivers/usb/host/ehci-oxnas.c
 *
 * Tzachi Perelstein <tzachi@marvell.com>
 *
 * This file is licensed under  the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/mbus.h>
#include <mach/mfctrl.h>
#include <mach/hw/sysctrl.h>
#include <mach/hw/secctrl.h>

static struct ox820_sysctrl_registers_t* const regs_sysctrl = (struct ox820_sysctrl_registers_t*) SYS_CONTROL_BASE;
static struct ox820_secctrl_registers_t* const regs_secctrl = (struct ox820_secctrl_registers_t*) SEC_CONTROL_BASE;

static int start_oxnas_usb_ehci(struct platform_device *dev)
{
	unsigned long input_polarity = 0;
	unsigned long output_polarity = 0;
	unsigned long power_polarity_default = regs_sysctrl->usbmph_ctrl;
	unsigned usb_hs_ifg;

	if (usb_disabled()) {
		printk(KERN_INFO "usb is disabled\n");
		return -ENODEV;
	}

	/*printk(KERN_INFO "starting usb for 820\n");
	printk("%s: block sizes: qh %Zd qtd %Zd itd %Zd sitd %Zd\n",
		hcd_name,
		sizeof (struct ehci_qh), sizeof (struct ehci_qtd),
		sizeof (struct ehci_itd), sizeof (struct ehci_sitd));

	printk(KERN_INFO "initialise for OX820 series USB\n");*/

#ifdef CONFIG_OXNAS_USB_OVERCURRENT_POLARITY_NEGATIVE
	input_polarity = (MSK_OX820_SYSCTRL_USBMPH_CTRL_IP_POL_A | MSK_OX820_SYSCTRL_USBMPH_CTRL_IP_POL_B);
#endif // CONFIG_OXNAS_USB_OVERCURRENT_POLARITY_NEGATIVE

#ifdef CONFIG_OXNAS_USB_POWER_SWITCH_POLARITY_NEGATIVE
	output_polarity = (MSK_OX820_SYSCTRL_USBMPH_CTRL_OP_POL_A | MSK_OX820_SYSCTRL_USBMPH_CTRL_OP_POL_B);
#endif // CONFIG_OXNAS_USB_POWER_SWITCH_POLARITY_NEGATIVE

	power_polarity_default &= ~0xf;
	usb_hs_ifg = (power_polarity_default >> 25) & 0x3f;
	usb_hs_ifg += 12;
	power_polarity_default &= ~(0x3f << 25);
	power_polarity_default |= (usb_hs_ifg << 25);
	power_polarity_default |= (input_polarity & 0x3);
	power_polarity_default |= (output_polarity & ( 0x3 <<2));

	regs_sysctrl->usbmph_ctrl = power_polarity_default;
	/*printk(KERN_INFO "usb hsmph ctrl set to:%#lx\n", power_polarity_default);*/

#ifdef CONFIG_OXNAS_USB_PORTA_POWER_CONTROL

#ifdef CONFIG_USB_PORTA_POWO_SECONDARY
	// Select USBA power output from secondary MFP function
	ox820_mf_select(OX820_MFA10_USBA_PWRO);
#endif // CONFIG_USB_PORTA_POWO_SECONDARY

#ifdef CONFIG_USB_PORTA_POWO_TERTIARY
	// Select USBA power output from tertiary MFP function
	ox820_mf_select(OX820_MFB16_USBA_PWRO);
#endif // CONFIG_USB_PORTA_POWO_TERTIARY

#ifdef CONFIG_USB_PORTA_OVERI_SECONDARY
	// Select USBA overcurrent from secondary MFP function
	ox820_mf_select(OX820_MFA11_USBA_OVERI);
#endif // CONFIG_USB_PORTA_OVERI_SECONDARY

#ifdef CONFIG_USB_PORTA_OVERI_TERTIARY
	// Select USBA overcurrent from tertiary MFP function
	ox820_mf_select(OX820_MFB17_USBA_OVERI);
#endif // CONFIG_USB_PORTA_OVERI_TERTIARY

#endif // CONFIG_OXNAS_USB_PORTA_POWER_CONTROL

#ifdef CONFIG_OXNAS_USB_PORTB_POWER_CONTROL

#ifdef CONFIG_USB_PORTB_POWO_SECONDARY
	// Select USBB power output from secondary MFP function
	ox820_mf_select(OX820_MFA28_USBB_PWRO);
#endif // CONFIG_USB_PORTB_POWO_SECONDARY

#ifdef CONFIG_USB_PORTB_POWO_TERTIARY
	// Select USBB power output from tertiary MFP function
	ox820_mf_select(OX820_MFA5_USBB_PWRO);
#endif // CONFIG_USB_PORTB_POWO_TERTIARY

#ifdef CONFIG_USB_PORTB_OVERI_SECONDARY
	// Select USBB overcurrent from secondary MFP function
	ox820_mf_select(OX820_MFA29_USBB_OVERI);
#endif // CONFIG_USB_PORTB_OVERI_SECONDARY

#ifdef CONFIG_USB_PORTB_OVERI_TERTIARY
	// Select USBB overcurrent from tertiary MFP function
	ox820_mf_select(OX820_MFA0_USBB_OVERI);
#endif // CONFIG_USB_PORTB_OVERI_TERTIARY

#endif // CONFIG_OXNAS_USB_PORTB_POWER_CONTROL

	// turn on internal 12MHz clock for OX820 architecture USB

	regs_sysctrl->cken_set_ctrl = MSK_OX820_SYSCTRL_CKEN_REF600;
	regs_sysctrl->rsten_clr_ctrl = MSK_OX820_SYSCTRL_RSTEN_PLLB;

	regs_sysctrl->ref300_div_ctrl = 25 << 8;  // ref 300 divider for 12MHz
	
	// Ensure the USB block is properly reset
	regs_sysctrl->rsten_set_ctrl = MSK_OX820_SYSCTRL_RSTEN_USBMPH;
	wmb();
	regs_sysctrl->rsten_clr_ctrl = MSK_OX820_SYSCTRL_RSTEN_USBMPH;
	regs_sysctrl->rsten_set_ctrl = MSK_OX820_SYSCTRL_RSTEN_USBPHYA;
	wmb();
	regs_sysctrl->rsten_clr_ctrl = MSK_OX820_SYSCTRL_RSTEN_USBPHYA;
	regs_sysctrl->rsten_set_ctrl = MSK_OX820_SYSCTRL_RSTEN_USBPHYB;
	wmb();
	regs_sysctrl->rsten_clr_ctrl = MSK_OX820_SYSCTRL_RSTEN_USBPHYB;

	// Force the high speed clock to be generated all the time, via serial
	// programming of the USB HS PHY
	regs_sysctrl->usbaphy_ctrl = (2 << BIT_OX820_SYSCTRL_USBPHY_CTRL_TEST_ADDR) |
				(0xE0 << BIT_OX820_SYSCTRL_USBPHY_CTRL_TEST_DIN);

	regs_sysctrl->usbaphy_ctrl = (2 << BIT_OX820_SYSCTRL_USBPHY_CTRL_TEST_ADDR) |
				(0xE0 << BIT_OX820_SYSCTRL_USBPHY_CTRL_TEST_DIN) |
				MSK_OX820_SYSCTRL_USBPHY_CTRL_TEST_CLK;

	regs_sysctrl->usbaphy_ctrl = (0xF << BIT_OX820_SYSCTRL_USBPHY_CTRL_TEST_ADDR) |
				(0xAA << BIT_OX820_SYSCTRL_USBPHY_CTRL_TEST_DIN);

	regs_sysctrl->usbaphy_ctrl = (0xF << BIT_OX820_SYSCTRL_USBPHY_CTRL_TEST_ADDR) |
				(0xAA << BIT_OX820_SYSCTRL_USBPHY_CTRL_TEST_DIN) |
				MSK_OX820_SYSCTRL_USBPHY_CTRL_TEST_CLK;

	/* select the correct clock now out of reset and USBA as host */
	regs_sysctrl->usb_ctrl = VAL_OX820_SYSCTRL_USB_CTRL_USBAPHY_CKSEL_INT | VAL_OX820_SYSCTRL_USB_CTRL_CKO_SEL_REF300_BCK;

	// Enable the clock to the USB block
	regs_sysctrl->cken_set_ctrl = MSK_OX820_SYSCTRL_CKEN_USBMPH;

	// Ensure reset and clock operations are complete
	wmb();
	
	return 0;
}


static int ehci_oxnas_setup(struct usb_hcd *hcd)
{
	struct ehci_hcd	*ehci;
	int temp;
	int retval;
	
	hcd->has_tt = 1;
	ehci = hcd_to_ehci(hcd);

	ehci->caps = hcd->regs;
	ehci->regs = hcd->regs + HC_LENGTH(ehci, readl(&ehci->caps->hc_capbase));
	dbg_hcs_params(ehci, "reset\n");
	dbg_hcc_params(ehci, "reset\n");

	/* cache this readonly data; minimize chip reads */
	ehci->hcs_params = readl(&ehci->caps->hcs_params);

	retval = ehci_halt(ehci);
	if (retval)
			return retval;

	/* data structure init */
	retval = ehci_init(hcd);
	if (retval)
		return retval;

	ehci->has_ppcd = 0;

	if (ehci_is_TDI(ehci))
		ehci_reset(ehci);

	/* at least the Genesys GL880S needs fixup here */
	temp = HCS_N_CC(ehci->hcs_params) * HCS_N_PCC(ehci->hcs_params);
	temp &= 0x0f;
	if (temp && HCS_N_PORTS(ehci->hcs_params) > temp) {
		ehci_dbg(ehci, "bogus port configuration: "
			"cc=%d x pcc=%d < ports=%d\n",
			HCS_N_CC(ehci->hcs_params),
			HCS_N_PCC(ehci->hcs_params),
			HCS_N_PORTS(ehci->hcs_params));
	}


	ehci_port_power(ehci, 0);

	return retval;
}

static const struct hc_driver ehci_oxnas_hc_driver = {
	.description = hcd_name,
	.product_desc = "OXNAS EHCI",
	.hcd_priv_size = sizeof(struct ehci_hcd),

	/*
	 * generic hardware linkage
	 */
	.irq = ehci_irq,
	.flags = HCD_MEMORY | HCD_USB2,

	/*
	 * basic lifecycle operations
	 */
	.reset = ehci_oxnas_setup,
	.start = ehci_run,
	.stop = ehci_stop,
	.shutdown = ehci_shutdown,

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue = ehci_urb_enqueue,
	.urb_dequeue = ehci_urb_dequeue,
	.endpoint_disable = ehci_endpoint_disable,
	.endpoint_reset = ehci_endpoint_reset,

	/*
	 * scheduling support
	 */
	.get_frame_number = ehci_get_frame,

	/*
	 * root hub support
	 */
	.hub_status_data = ehci_hub_status_data,
	.hub_control = ehci_hub_control,
	.bus_suspend = ehci_bus_suspend,
	.bus_resume = ehci_bus_resume,
	.relinquish_port = ehci_relinquish_port,
	.port_handed_over = ehci_port_handed_over,

	.clear_tt_buffer_complete = ehci_clear_tt_buffer_complete,
};

static int __devinit ehci_oxnas_drv_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct usb_hcd *hcd;
	struct ehci_hcd *ehci;
	void __iomem *regs;
	int irq, err;

	if (usb_disabled())
		return -ENODEV;

	printk("Initializing Oxnas-SoC USB Host Controller\n");

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0) {
		dev_err(&pdev->dev,
			"Found HC with no IRQ. Check %s setup!\n",
			dev_name(&pdev->dev));
		err = -ENODEV;
		goto err1;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev,
			"Found HC with no register addr. Check %s setup!\n",
			dev_name(&pdev->dev));
		err = -ENODEV;
		goto err1;
	}

	if (!request_mem_region(res->start, resource_size(res),
				ehci_oxnas_hc_driver.description)) {
		dev_dbg(&pdev->dev, "controller already in use\n");
		err = -EBUSY;
		goto err1;
	}

	regs = ioremap(res->start, resource_size(res));
	if (regs == NULL) {
		dev_dbg(&pdev->dev, "error mapping memory\n");
		err = -EFAULT;
		goto err2;
	}
	start_oxnas_usb_ehci(pdev);

	hcd = usb_create_hcd(&ehci_oxnas_hc_driver,
			&pdev->dev, dev_name(&pdev->dev));
	if (!hcd) {
		err = -ENOMEM;
		goto err3;
	}

	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);
	hcd->regs = regs;//(void *)(USBHOST_BASE  + 0x100); //regs;

	/*printk(KERN_INFO "@%p Device ID register %lx\n", (void *)USBHOST_BASE, *(unsigned long *)USBHOST_BASE);*/

	hcd->has_tt = 1;
	ehci = hcd_to_ehci(hcd);
	ehci->caps = hcd->regs;
	ehci->regs = hcd->regs +
		HC_LENGTH(ehci, ehci_readl(ehci, &ehci->caps->hc_capbase));
	ehci->hcs_params = ehci_readl(ehci, &ehci->caps->hcs_params);
	ehci->sbrn = 0x20;



	err = usb_add_hcd(hcd, irq, IRQF_SHARED | IRQF_DISABLED);
	if (err)
		goto err4;

	return 0;

err4:
	usb_put_hcd(hcd);
err3:
	iounmap(regs);
err2:
	release_mem_region(res->start, resource_size(res));
err1:
	dev_err(&pdev->dev, "init %s fail, %d\n",
		dev_name(&pdev->dev), err);

	return err;
}

static int __exit ehci_oxnas_drv_remove(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);

	usb_remove_hcd(hcd);
	iounmap(hcd->regs);
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
	usb_put_hcd(hcd);

	return 0;
}

MODULE_ALIAS("platform:ox820-ehci");

static struct platform_driver ehci_oxnas_driver = {
	.probe		= ehci_oxnas_drv_probe,
	.remove		= __exit_p(ehci_oxnas_drv_remove),
	.shutdown	= usb_hcd_platform_shutdown,
	.driver.name	= "oxnas-ehci",
};
