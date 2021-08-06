/****************************************************************************
 * Ralink Tech Inc.
 * Taiwan, R.O.C.
 *
 * (c) Copyright 2002, Ralink Technology, Inc.
 *
 * All rights reserved. Ralink's source code is an unpublished work and the
 * use of a copyright notice does not imply otherwise. This source code
 * contains confidential trade secret material of Ralink Tech. Any attemp
 * or participation in deciphering, decoding, reverse engineering or in any
 * way altering the source code is stricitly prohibited, unless the prior
 * written consent of Ralink Technology, Inc. is obtained.
 ***************************************************************************/

/****************************************************************************

	Abstract:

	All MAC80211/CFG80211 Related Structure & Definition.

***************************************************************************/
#ifndef __CFG80211_H__
#define __CFG80211_H__

#ifdef RT_CFG80211_SUPPORT

#include <linux/ieee80211.h>

extern UCHAR Cfg80211_Chan[];
extern const int Num_Cfg80211_Chan;

#define RT_REG_RULE(regr, start, end, bw, gain, eirp, reg_flags) \
	do {                                                \
		regr.freq_range.start_freq_khz = MHZ_TO_KHZ(start);	\
		regr.freq_range.end_freq_khz = MHZ_TO_KHZ(end);	\
		regr.freq_range.max_bandwidth_khz = MHZ_TO_KHZ(bw);	\
		regr.power_rule.max_antenna_gain = DBI_TO_MBI(gain);\
		regr.power_rule.max_eirp = DBM_TO_MBM(eirp);	\
		regr.flags = reg_flags;                         \
	} while (0)

typedef enum _NDIS_HOSTAPD_STATUS {
	Hostapd_Diable = 0,
	Hostapd_EXT,
	Hostapd_CFG
} NDIS_HOSTAPD_STATUS, *PNDIS_HOSTAPD_STATUS;

#ifdef JUNGLE_SUPPORT
/*  the following define just for compile, please follow the definition of include/cfg80211.h
*	the value only sync with kernel 3.10
*/
#define IEEE80211_CHAN_PASSIVE_SCAN	(1<<1)
#define IEEE80211_CHAN_RADAR (1<<3)
struct _CH_FLAGS_BEACON {
	UCHAR ch;
	UINT32 flags;
};
#endif

typedef struct __CFG80211_CB {

    #if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
    #define ieee80211_band nl80211_band
    #define IEEE80211_BAND_2GHZ NL80211_BAND_2GHZ
    #define IEEE80211_BAND_5GHZ NL80211_BAND_5GHZ
    #define IEEE80211_NUM_BANDS NUM_NL80211_BANDS
    #endif

	/* we can change channel/rate information on the fly so we backup them */
	struct ieee80211_supported_band Cfg80211_bands[IEEE80211_NUM_BANDS];
	struct ieee80211_channel *pCfg80211_Channels;
	struct ieee80211_rate *pCfg80211_Rates;

	/* used in wiphy_unregister */
	struct wireless_dev *pCfg80211_Wdev;

	/* used in scan end */
	struct cfg80211_scan_request *pCfg80211_ScanReq;

	/* monitor filter */
	UINT32 MonFilterFlag;
#ifdef JUNGLE_SUPPORT
	struct _CH_FLAGS_BEACON *ch_flags_by_beacon;
#endif
	/* channel information */
	struct ieee80211_channel ChanInfo[MAX_NUM_OF_CHANNELS];

	/* to protect scan status */
	spinlock_t scan_notify_lock;

	BOOLEAN ScanIsAborted;   /*MLME BUSY*/

} CFG80211_CB;

/*
========================================================================
Routine Description:
	Register MAC80211 Module.

Arguments:
	pAd				- WLAN control block pointer
	pDev			- Generic device interface
	pNetDev			- Network device

Return Value:
	NONE

Note:
	pDev != pNetDev
	#define SET_NETDEV_DEV(net, pdev)	((net)->dev.parent = (pdev))

	Can not use pNetDev to replace pDev; Or kernel panic.
========================================================================
*/
BOOLEAN CFG80211_Register(VOID *pAd, struct device *pDev, struct net_device *pNetDev);

#endif /* RT_CFG80211_SUPPORT */

#endif /* __CFG80211_H__ */

/* End of cfg80211.h */
