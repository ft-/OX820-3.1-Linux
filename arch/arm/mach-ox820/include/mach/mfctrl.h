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
 */

#ifndef _ox820_mach_mfctrl_h
#define _ox820_mach_mfctrl_h

#include <linux/types.h>

enum ox820_mfctrl_t
{
    /**********************************/
    OX820_MF_PRIMARY_BASE = 0,
    
    OX820_MFA0_GPIO = 0,
    OX820_MFA1_GPIO = 1,
    OX820_MFA2_GPIO = 2,
    OX820_MFA3_GPIO = 3,
    OX820_MFA4_GPIO = 4,
    OX820_MFA5_GPIO = 5,
    OX820_MFA6_GPIO = 6,
    OX820_MFA7_GPIO = 7,
    OX820_MFA8_GPIO = 8,
    OX820_MFA9_GPIO = 9,
    OX820_MFA10_GPIO = 10,
    OX820_MFA11_GPIO = 11,
    OX820_MFA12_GPIO = 12,
    OX820_MFA13_GPIO = 13,
    OX820_MFA14_GPIO = 14,
    OX820_MFA15_GPIO = 15,
    OX820_MFA16_GPIO = 16,
    OX820_MFA17_GPIO = 17,
    OX820_MFA18_GPIO = 18,
    OX820_MFA19_GPIO = 19,
    OX820_MFA20_GPIO = 20,
    OX820_MFA21_GPIO = 21,
    OX820_MFA22_GPIO = 22,
    OX820_MFA23_GPIO = 23,
    OX820_MFA24_GPIO = 24,
    OX820_MFA25_GPIO = 25,
    OX820_MFA26_GPIO = 26,
    OX820_MFA27_GPIO = 27,
    OX820_MFA28_GPIO = 28,
    OX820_MFA29_GPIO = 29,
    OX820_MFA30_GPIO = 30,
    OX820_MFA31_GPIO = 31,
    OX820_MFB0_GPIO = 32,
    OX820_MFB1_GPIO = 33,
    OX820_MFB2_GPIO = 34,
    OX820_MFB3_GPIO = 35,
    OX820_MFB4_GPIO = 36,
    OX820_MFB5_GPIO = 37,
    OX820_MFB6_GPIO = 38,
    OX820_MFB7_GPIO = 39,
    OX820_MFB8_GPIO = 40,
    OX820_MFB9_GPIO = 41,
    OX820_MFB10_GPIO = 42,
    OX820_MFB11_GPIO = 43,
    OX820_MFB12_GPIO = 44,
    OX820_MFB13_GPIO = 45,
    OX820_MFB14_GPIO = 46,
    OX820_MFB15_GPIO = 47,
    OX820_MFB16_GPIO = 48,
    OX820_MFB17_GPIO = 49,
    
    /**********************************/
    OX820_MF_ALTERNATE_BASE = 1000,
    
    OX820_MFA28_UARTA_CTS_N = 1028,
    OX820_MFA29_UARTA_RTS_N = 1029,
    OX820_MFA30_UARTA_SIN = 1030,
    OX820_MFA31_UARTA_SOUT = 1031,
    OX820_MFB12_UARTB_CTS_N = 1044,
    OX820_MFB12_UARTB_RTS_N = 1045,
    OX820_MFB12_UARTB_SIN = 1046,
    OX820_MFB12_UARTB_SOUT = 1047,
    
    /**********************************/
    OX820_MF_SECONDARY_BASE = 2000,
    
    OX820_MFA3_ETHA_MDC = 2003,
    OX820_MFA4_ETHA_MDIO = 2004,
    OX820_MFA10_USBA_PWRO = 2010,
    OX820_MFA11_USBA_OVERI = 2011,
    OX820_MFA12_STATIC_DATA0 = 2012,
    OX820_MFA13_STATIC_DATA1 = 2013,
    OX820_MFA14_STATIC_DATA2 = 2014,
    OX820_MFA15_STATIC_DATA3 = 2015,
    OX820_MFA16_STATIC_DATA4 = 2016,
    OX820_MFA17_STATIC_DATA5 = 2017,
    OX820_MFA18_STATIC_DATA6 = 2018,
    OX820_MFA19_STATIC_DATA7 = 2019,
    OX820_MFA20_STATIC_WE_N = 2020,
    OX820_MFA21_STATIC_OE_N = 2021,
    OX820_MFA22_STATIC_CS0_N = 2022,
    OX820_MFA23_STATIC_ADDR18 = 2023,
    OX820_MFA24_STATIC_ADDR19 = 2024,
    OX820_MFA25_STATIC_CS1_N = 2025,
    OX820_MFA28_USBB_PWRO = 2028,
    OX820_MFA29_USBB_OVERI = 2029,
    OX820_MFA30_STATIC_ADDR20 = 2030,
    OX820_MFA31_STATIC_ADDR21 = 2031,
    OX820_MFB0_STATIC_ADDR0 = 2032,
    OX820_MFB1_STATIC_ADDR1 = 2033,
    OX820_MFB2_STATIC_ADDR2 = 2034,
    OX820_MFB3_STATIC_ADDR3 = 2035,
    OX820_MFB4_STATIC_ADDR4 = 2036,
    OX820_MFB5_STATIC_ADDR5 = 2037,
    OX820_MFB6_STATIC_ADDR6 = 2038,
    OX820_MFB7_STATIC_ADDR7 = 2039,
    OX820_MFB8_STATIC_ADDR8 = 2040,
    OX820_MFB9_STATIC_ADDR9 = 2041,
    OX820_MFB10_STATIC_ADDR10 = 2042,
    OX820_MFB11_STATIC_ADDR11 = 2043,
    OX820_MFB12_STATIC_ADDR12 = 2044,
    OX820_MFB13_STATIC_ADDR13 = 2045,
    OX820_MFB14_STATIC_ADDR14 = 2046,
    OX820_MFB15_STATIC_ADDR15 = 2047,
    OX820_MFB16_STATIC_ADDR16 = 2048,
    OX820_MFB17_STATIC_ADDR17 = 2049,
    
    /**********************************/
    OX820_MF_TERTIARY_BASE = 3000,
    
    OX820_MFA0_USBB_OVERI = 3000,
    OX820_MFA5_USBB_PWRO = 3005,
    OX820_MFA12_USBA_VBUS = 3012,
    OX820_MFB16_USBA_PWRO = 3048,
    OX820_MFB17_USBA_OVERI = 3049,
    
    /**********************************/
    OX820_MF_QUATERARY_BASE = 4000,
    
    /**********************************/
    OX820_MF_DEBUG_BASE = 5000,
    
    OX820_MFA5_UARTB_CTS_N = 5005,
    OX820_MFA5_UARTB_RTS_N = 5006,
    OX820_MFA7_UARTB_SIN = 5007,
    OX820_MFA8_UARTB_SOUT = 5008,
    OX820_MFA11_UARTA_SIN = 5011,
    OX820_MFA12_UARTA_SOUT = 5012,
    OX820_MFA13_UARTA_CTS_N = 5013,
    OX820_MFA14_UARTA_RTS_N = 5014,
    OX820_MFA24_UARTA_RI_N = 5024,
    OX820_MFA25_UARTA_CD_N = 5025,
    OX820_MFA26_UARTA_DSR_N = 5026,
    OX820_MFA27_UARTA_DTR_N = 5027,
    OX820_MFB8_UARTB_RI_N = 5040,
    OX820_MFB9_UARTB_CD_N = 5041,
    OX820_MFB10_UARTB_DSR_N = 5042,
    OX820_MFB11_UARTB_DTR_N = 5043,
};

enum ox820_mfctrl_direction_t
{
    OX820_DIR_INPUT,
    OX820_DIR_OUTPUT
};

void ox820_mf_select(enum ox820_mfctrl_t);
void ox820_mf_set_gpio_direction(enum ox820_mfctrl_t, enum ox820_mfctrl_direction_t direction);

void ox820_mf_select_gpio(u32 gpionr);
void ox820_mf_select_static(u32 address_lines, u32 cs_lines);

#endif
