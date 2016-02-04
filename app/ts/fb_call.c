
2016年 01月 29日 星期五 20:05:41 CST

root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # dmesg -c                                                         
[19700102_16:54:08.500729]@0 hvdcpd: Couldnt read parallel input_current_limited rc = -2
[19700102_16:54:09.096086]@0 Power-Key DOWN
[19700102_16:54:09.111283]@2 blank on start							==============>
[19700102_16:54:09.111315]@2 fpc1020 soc:fpc_fpc1020: fb_notifier_callback screen on
[19700102_16:54:09.116473]@1 fpc1020 soc:fpc_fpc1020: fpc1020_irq_handler
[19700102_16:54:09.119450]@2 mdss_dsi_on start
[19700102_16:54:09.122391]@2 fpc1020 soc:fpc_fpc1020: fpc1020_irq_handler
[19700102_16:54:09.129569]@2 fpc1020 soc:fpc_fpc1020: fpc1020_irq_handler
[19700102_16:54:09.161440]@1 cnss_wlan_pci 0000:01:00.0: Refused to change power state, currently in D3
[19700102_16:54:09.161618]@1 msm_pcie_enable: PCIe: Assert the reset of endpoint of RC0.
[19700102_16:54:09.165317]@1 msm_pcie_enable: PCIe RC0 PHY is ready!
[19700102_16:54:09.175515]@1 msm_pcie_enable: PCIe: Release the reset of endpoint of RC0.
[19700102_16:54:09.190954]@1 mdss_dsi_on end
[19700102_16:54:09.193646]@0 i2c-msm-v2 75b6000.i2c: NACK: slave not responding, ensure its powered: msgs(n:1 cur:0 tx) bc(rx:0 tx:4) mode:FIFO slv_addr:0x28 MSTR_STS:0x0d1300c8 OPER:0x00000090
[19700102_16:54:09.193719]@0 pn544_dev_write : i2c_master_send returned -107
[19700102_16:54:09.203803]@1 msm_pcie_enable: PCIe RC0 link initialized
[19700102_16:54:09.221512]@1 cnss_wlan_pci 0000:01:00.0: enabling device (0000 -> 0002)
[19700102_16:54:09.227134]@0 wlan: [0:F :WDA] WOW wakeup host event received (reason: RUNTIME PM resume(-1)) for vdev 0
[19700102_16:54:09.227286]@1 __hif_pci_resume: Resume completes for runtime pm in wow mode
[19700102_16:54:09.227432]@1 cnss: runtime resume status: 0
[19700102_16:54:09.227446]@1 hif_pci_pm_work: Resume HTT & WMI Service in runtime_pm state 1
[19700102_16:54:09.228055]@2 synaptics,s3320: synaptics_ts_resume enter!
[19700102_16:54:09.228114]@2 synaptics,s3320: synaptics_ts_resume:normal end!
[19700102_16:54:09.228389]@2 blank on end							===============> fb 回调完成。
[19700102_16:54:09.271725]@3 mdss_dsi_post_panel_on:-
[19700102_16:54:09.271817]@3 --------backlight level = 32---------
[19700102_16:54:09.301665]@0 Power-Key UP
[19700102_16:54:09.473338]@3 synaptics,s3320: synaptics_mode_change: set TP to mode[0x80]
[19700102_16:54:09.725911]@1 __hif_pci_suspend: Waiting for CE to finish access: 
[19700102_16:54:09.750831]@1 __hif_pci_suspend: Suspend completes for runtime pm in wow mode event:2 device_state:-65
[19700102_16:54:09.750882]@1 __hif_pci_suspend: Suspend completes for runtime pm
[19700102_16:54:09.792760]@1 msm_pcie_disable: PCIe: Assert the reset of endpoint of RC0.
[19700102_16:54:09.796033]@1 cnss: runtime suspend status: 0
[19700102_16:54:09.812176]@1 cnss_wlan_pci 0000:01:00.0: Refused to change power state, currently in D3
[19700102_16:54:09.813751]@1 msm_pcie_enable: PCIe: Assert the reset of endpoint of RC0.
[19700102_16:54:09.819468]@1 msm_pcie_enable: PCIe RC0 PHY is ready!
[19700102_16:54:09.829928]@1 msm_pcie_enable: PCIe: Release the reset of endpoint of RC0.
[19700102_16:54:09.857991]@1 msm_pcie_enable: PCIe RC0 link initialized
[19700102_16:54:09.881889]@1 cnss_wlan_pci 0000:01:00.0: enabling device (0000 -> 0002)
[19700102_16:54:09.891346]@0 wlan: [0:F :WDA] WOW wakeup host event received (reason: RUNTIME PM resume(-1)) for vdev 0
[19700102_16:54:09.891616]@1 __hif_pci_resume: Resume completes for runtime pm in wow mode
[19700102_16:54:09.891775]@1 cnss: runtime resume status: 0
[19700102_16:54:09.891829]@1 hif_pci_pm_work: Resume HTT & WMI Service in runtime_pm state 1
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # dmesg -c                                                         
[19700102_16:54:11.266648]@0 wlan: [43:E :WDA]  scan complete - scan_id a007, vdev_id 0
[19700102_16:54:11.275888]@0 wlan: [2071:E :SME] Found 67 BSS, statusCode 0
[19700102_16:54:11.816558]@0 __hif_pci_suspend: Suspend completes for runtime pm in wow mode event:2 device_state:-65
[19700102_16:54:11.816610]@0 __hif_pci_suspend: Suspend completes for runtime pm
[19700102_16:54:11.853549]@0 msm_pcie_disable: PCIe: Assert the reset of endpoint of RC0.
[19700102_16:54:11.856019]@0 cnss: runtime suspend status: 0
[19700102_16:54:13.903544]@0 Power-Key DOWN
[19700102_16:54:14.086499]@0 Power-Key UP
[19700102_16:54:14.504539]@3 hvdcpd: Couldnt read parallel input_current_limited rc = -2
[19700102_16:54:14.590417]@1 --------backlight level = 0---------
==================================================================================================
				//丢失了....
[19700102_16:54:14.614019]@1 blank off start		---> fbmem.c
[19700102_16:54:14.614051]@1 fpc1020 soc:fpc_fpc1020: fb_notifier_callback screen off
[19700102_16:54:14.614081]@1 synaptics,s3320: synaptics_ts_suspend enter
[19700102_16:54:14.623530]@2 fpc1020 soc:fpc_fpc1020: fpc1020_irq_handler
[19700102_16:54:14.624804]@1 synaptics,s3320: synaptics_mode_change: set TP to mode[0x1]
[19700102_16:54:14.625169]@1 synaptics,s3320: synaptics_ts_suspend normal end
[19700102_16:54:14.850539]@1 mdss_dsi_off start
[19700102_16:54:14.897236]@1 mdss_dsi_off end
[19700102_16:54:14.901517]@1 blank off end
==================================================================================================
[19700102_16:54:14.941512]@3 cnss_wlan_pci 0000:01:00.0: Refused to change power state, currently in D3
[19700102_16:54:14.941747]@3 msm_pcie_enable: PCIe: Assert the reset of endpoint of RC0.
[19700102_16:54:14.945714]@3 msm_pcie_enable: PCIe RC0 PHY is ready!
[19700102_16:54:14.948007]@0 i2c-msm-v2 75b6000.i2c: NACK: slave not responding, ensure its powered: msgs(n:1 cur:0 tx) bc(rx:0 tx:4) mode:FIFO slv_addr:0x28 MSTR_STS:0x0d1300c8 OPER:0x00000090
[19700102_16:54:14.948124]@2 pn544_dev_write : i2c_master_send returned -107
[19700102_16:54:14.955912]@3 msm_pcie_enable: PCIe: Release the reset of endpoint of RC0.
[19700102_16:54:14.983477]@3 msm_pcie_enable: PCIe RC0 link initialized
[19700102_16:54:15.001619]@3 cnss_wlan_pci 0000:01:00.0: enabling device (0000 -> 0002)
[19700102_16:54:15.008296]@0 wlan: [0:F :WDA] WOW wakeup host event received (reason: RUNTIME PM resume(-1)) for vdev 0
[19700102_16:54:15.008462]@3 __hif_pci_resume: Resume completes for runtime pm in wow mode
[19700102_16:54:15.008525]@3 cnss: runtime resume status: 0
[19700102_16:54:15.008550]@3 hif_pci_pm_work: Resume HTT & WMI Service in runtime_pm state 1
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # hyh@hyh-OptiPlex-9020:~/workspace/test/test_app_ts/app/ts$

Compiled on Jan  1 2014, 17:13:19.
Port /dev/ttyUSB0, 20:08:25

Press CTRL-A Z for help on special keys

AT+EDFT=6,1
OK
AT+PRINTK=0,1
OK[19700102_17:04:02.047800]@0 FTM: at_enable_kernel_print - OK
AT+ESLP=1
[19700102_17:04:16.856972]@0 blank off start
[19700102_17:04:16.857060]@0 fpc1020 soc:fpc_fpc1020: fb_notifier_callback scref
				//没有调用到s3320.c
[19700102_17:04:16.857276]@0 blank off end
OK[19700102_17:04:17.877009]@0 FTM: at_sleep_enable - OK
[19700102_17:04:17.989073]@0 PM: suspend entry 
1970-01-02 09:04:17.989043022 UTC
[19700102_17:04:17.996782]@0 PM: Syncing filesystems ... 
[19700102_17:04:18.021.
[19700102_17:04:18.047080]@0 Freezing user space processes ... 
[19700102_17:04:18.057389]@0 Error: returning -512 value
[19700102_17:04:18.062352]@0 PM: Wakeup pending, aborting suspend
[19700102_17:04:18.067571]@0 last active wakeup source: eventpoll               
[19700102_17:04:18.073629]@0                                                    
[19700102_17:04:18.075964]@0 Freezing of tasks aborted after 0.019 seconds[1970 
[19700102_17:04:18.085078]@0 Restarting tasks ... [19700102_17:04:18.094844]@0 .
[19700102_17:04:18.097513]@0 PM: suspend exit 1970-01-02 09:04:18.097499324 UTC 
[19700102_17:04:18.207735]@0 PM: suspend entry 1970-01-02 09:04:18.207711251 UTC
[19700102_17:04:18.216026]@0 PM: Syncing filesystems ... [19700102_17:04:18.226.
[19700102_17:04:18.232838]@0 Freezing user space processes ...                  
[19700102_17:04:18.241773]@0 Error: returning -512 value                        
[19700102_17:04:18.253194]@0 (elapsed 0.015 seconds) [19700102_17:04:18.256838] 
[19700102_17:04:18.262476]@0 Freezing remaining freezable tasks ... [19700102_1 
[19700102_17:04:18.283570]@0 Suspending console(s) (use no_console_suspend to d)
CTRL-A Z for help | 115200 8N1 | NOR | Minicom 2.7 | VT102 | Offline | ttyUSB0 
hyh@hyh-OptiPlex-9020:~$ sudo minicom 


AT+ESLP=0
OK[19700102_17:07:45.577505]@0 FTM: at_sleep_disable - OK
[19700102_17:07:53.158935]@0 Power-Key DOWN
[19700102_17:07:53.402221]@0 Power-Key UP
[19700102_17:07:54.583472]@0 Power-Key DOWN
[19700102_17:07:54.826327]@0 Power-Key UP



AT+ESLP=1                                                                       
[19700102_17:08:10.671670]@0 blank off start                                    
[19700102_17:08:10.671739]@0 fpc1020 soc:fpc_fpc1020: fb_notifier_callback scref
[19700102_17:08:10.671929]@0 blank off end                                      
                                                

==========================================bug
fbmem.c

debug_blank(blank,1);	---> 正常.

early_ret = fb_notifier_call_chain(FB_EARLY_EVENT_BLANK, &event);

if (info->fbops->fb_blank)
	ret = info->fbops->fb_blank(blank, info);

if (!ret)
	fb_notifier_call_chain(FB_EVENT_BLANK, &event);
	else {
		/*
		 * if fb_blank is failed then revert effects of
		 * the early blank event.
		 */
		if (!early_ret)
			fb_notifier_call_chain(FB_R_EARLY_EVENT_BLANK, &event);
	}

/*ykl add debug log*/
debug_blank(blank,0);	---> 结束》


=====================================
2016年 01月 31日 星期日 18:53:55 CST



root@RAIN:/ # dmesg  -c | grep -E "fpc|hyh|blank|s3320"                        
[19700104_16:10:10.295921]@3 blank off start
[19700104_16:10:10.295951]@3 fpc1020 soc:fpc_fpc1020: fb_notifier_callback blank[4],event[0x10]   hyh:ffffffc00070ba48
[19700104_16:10:10.295962]@3 fpc1020 soc:fpc_fpc1020: fb_notifier_callback screen off
[19700104_16:10:10.296096]@3 synaptics,s3320: synaptics_ts_suspend enter
[19700104_16:10:10.298906]@2 synaptics,s3320: synaptics_mode_change: set TP to mode[0x1]
[19700104_16:10:10.299756]@2 synaptics,s3320: synaptics_ts_suspend normal end
[19700104_16:10:10.299778]@2  hyh1:0
[19700104_16:10:10.573094]@1  hyh2:0
[19700104_16:10:10.573117]@1 fpc1020 soc:fpc_fpc1020: fb_notifier_callback blank[4],event[0x9]   hyh:ffffffc00070ba48
[19700104_16:10:10.575182]@1 blank off end
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # dmesg  -c | grep -E "fpc|hyh|blank|s3320"                        
[19700104_16:10:14.846828]@2 blank on start
[19700104_16:10:14.846863]@2 fpc1020 soc:fpc_fpc1020: fb_notifier_callback blank[0],event[0x10]   hyh:ffffffc00070ba48
[19700104_16:10:14.846870]@2 fpc1020 soc:fpc_fpc1020: fb_notifier_callback screen on
[19700104_16:10:14.846951]@2  hyh1:0
[19700104_16:10:14.985636]@2  hyh2:0
[19700104_16:10:14.985687]@2 fpc1020 soc:fpc_fpc1020: fb_notifier_callback blank[0],event[0x9]   hyh:ffffffc00070ba48
[19700104_16:10:14.985694]@2 synaptics,s3320: synaptics_ts_resume enter!
[19700104_16:10:14.985769]@2 synaptics,s3320: synaptics_ts_resume:normal end!
[19700104_16:10:14.991433]@0 blank on end
[19700104_16:10:15.288589]@3 synaptics,s3320: synaptics_mode_change: set TP to mode[0x80]
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # 



\\172.21.106.141\sw_release\MSM8996\15801\DailyBuild\Release\HYDROGEN\MSM_15801_160114_0500_user
这个版本  ftm mode 触摸屏幕不能待机.


---------------------------------------------------------------------------------
需要确认 14号之前的版本是否 at模式 fb_notifier_callback  s3320 中会调用.

确认client 都被调用.
---------------------------------------------------------------------------------
需要确认 xx号之后的版本是否 at模式 fb_notifier_callback  s3320 中会调用.

---------------------------------------------------------------------------------
找出原因，查看提交记录.


2016-1-14/31		去掉fpc1020 中的客户端。

root@RAIN:/ # dmesg -c                                                         
[19700101_22:06:57.204737]@3 synaptics,s3320: all finger up
[19700101_22:06:57.347732]@0 i2c-msm-v2 75b6000.i2c: NACK: slave not responding, ensure its powered: msgs(n:1 cur:0 tx) bc(rx:0 tx:4) mode:FIFO slv_addr:0x28 MSTR_STS:0x0d1300c8 OPER:0x00000090
[19700101_22:06:57.347856]@2 pn544_dev_write : i2c_master_send returned -107
[19700101_22:06:58.303239]@0 Power-Key DOWN
[19700101_22:06:58.553018]@0 Power-Key UP
[19700101_22:06:59.055156]@2 --------backlight level = 0---------
[19700101_22:06:59.161130]@0 blank off start
[19700101_22:06:59.161147]@0 synaptics,s3320: synaptics_ts_suspend enter
[19700101_22:06:59.163663]@0 synaptics,s3320: synaptics_mode_change: set TP to mode[0x1]
[19700101_22:06:59.164310]@0 synaptics,s3320: synaptics_ts_suspend normal end
[19700101_22:06:59.164320]@0  hyh1:0
[19700101_22:06:59.383225]@1 mdss_dsi_off start
[19700101_22:06:59.428785]@1 mdss_dsi_off end
[19700101_22:06:59.435923]@1  hyh2:0
[19700101_22:06:59.438361]@0 blank off end
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # dmesg -c                                                         
[19700101_22:07:01.120208]@0 Power-Key DOWN
[19700101_22:07:01.145441]@0 blank on start
[19700101_22:07:01.145534]@0  hyh1:0
[19700101_22:07:01.157409]@1 mdss_dsi_on start
[19700101_22:07:01.232190]@2 mdss_dsi_on end
[19700101_22:07:01.239691]@0 i2c-msm-v2 75b6000.i2c: NACK: slave not responding, ensure its powered: msgs(n:1 cur:0 tx) bc(rx:0 tx:4) mode:FIFO slv_addr:0x28 MSTR_STS:0x0d1300c8 OPER:0x00000090
[19700101_22:07:01.239766]@0 pn544_dev_write : i2c_master_send returned -107
[19700101_22:07:01.267092]@2  hyh2:0
[19700101_22:07:01.267109]@2 synaptics,s3320: synaptics_ts_resume enter!
[19700101_22:07:01.267160]@2 synaptics,s3320: synaptics_ts_resume:normal end!
[19700101_22:07:01.267532]@2 blank on end
[19700101_22:07:01.267736]@0 Power-Key UP
[19700101_22:07:01.312591]@3 mdss_dsi_post_panel_on:-
[19700101_22:07:01.312689]@3 --------backlight level = 34---------
[19700101_22:07:01.515476]@2 synaptics,s3320: synaptics_mode_change: set TP to mode[0x80]
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # 

AT+PRINTK=0,1
OK[19700101_22:10:06.338003]@0 FTM: at_enable_kernel_print - OK

AT+ESLP=1
[19700101_22:10:20.953739]@0 blank off start
[19700101_22:10:20.953822]@0  hyh1:0
[19700101_22:10:20.954055]@0  hyh2:0
[19700101_22:10:20.954092]@0 blank off end
OK[19700101_22:10:21.979596]@0 FTM: at_sleep_enable - OK





2016年 02月 01日 星期一 09:46:05 CST
===============================================
AT+EDFT=0,0
[19700102_00:24:43.182172]@0 blank off start
[19700102_00:24:43.182260]@0 fpc1020 soc:fpc_fpc1020: fb_notifier_callback screen off
[19700102_00:24:43.182393]@0 synaptics,s3320: synaptics_ts_suspend enter
[19700102_00:24:43.185486]@0 synaptics,s3320: synaptics_mode_change: set TP to mode[0x1]
[19700102_00:24:43.186930]@0 synaptics,s3320: synaptics_ts_suspend normal end
[19700102_00:24:43.187263]@0 --------backlight level = 0---------
[19700102_00:24:43.434335]@0 mdss_dsi_off start
[19700102_00:24:43.478281]@0 mdss_dsi_off end                                                                      
[19700102_00:24:43.483579]@0 blank off end                                                                         
OK[19700102_00:24:43.535299]@0 FTM: at_lcd_backlight_off - OK                                                      


AT+EDFT=0,5
[19700102_00:25:34.711235]@0 blank on start
[19700102_00:25:34.711320]@0 fpc1020 soc:fpc_fpc1020: fb_notifier_callback screen on
[19700102_00:25:34.717320]@0 mdss_dsi_on start
[19700102_00:25:34.792739]@0 mdss_dsi_on end
[19700102_00:25:34.829598]@0 synaptics,s3320: synaptics_ts_resume enter!
[19700102_00:25:34.829742]@0 synaptics,s3320: synaptics_ts_resume:normal end!
[19700102_00:25:34.832584]@0 blank on end
[19700102_00:25:34.890571]@0 mdss_dsi_post_panel_on:-
[19700102_00:25:34.895227]@0 --------backlight level = 100---------
OK[19700102_00:25:34.913111]@0 FTM: at_lcd_backlight_on - OK
[19700102_00:25:35.099862]@0 synaptics,s3320: synaptics_mode_change: set TP to mode[0x80]


AT+EDFT=0,0
[19700102_00:33:02.454611]@0 blank off start
[19700102_00:33:02.454696]@0 fpc1020 soc:fpc_fpc1020: fb_notifier_callback screen off
[19700102_00:33:02.454832]@0 synaptics,s3320: synaptics_ts_suspend enter
[19700102_00:33:02.459470]@0 synaptics,s3320: synaptics_mode_change: set TP to mode[0x1]   已经进入到suspend 
[19700102_00:33:02.460687]@0 synaptics,s3320: synaptics_ts_suspend normal end
[19700102_00:33:02.461001]@0 --------backlight level = 0---------
[19700102_00:33:02.708410]@0 mdss_dsi_off start
[19700102_00:33:02.758278]@0 mdss_dsi_off end
[19700102_00:33:02.763586]@0 blank off end
OK[19700102_00:33:02.814642]@0 FTM: at_lcd_backlight_off - OK


AT+ESLP=1
[19700102_00:42:15.137249]@0 blank off start
[19700102_00:42:15.137334]@0 fpc1020 soc:fpc_fpc1020: fb_notifier_callback screen off   不会进入到suspend
[19700102_00:42:15.137707]@0 blank off end
OK[19700102_00:42:16.157564]@0 FTM: at_sleep_enable - OK
[19700102_00:42:16.269518]@0 PM: suspend entry 1970-01-01 16:42:16.269488424 UTC
[19700102_00:42:16.277231]@0 PM: Syncing filesystems ... [19700102_00:42:16.298867]@0 done.
[19700102_00:42:16.330017]@0 Freezing user space processes ... 
[19700102_00:42:16.341008]@0 Error: returning -512 value
[19700102_00:42:16.345803]@0 PM: Wakeup pending, aborting suspend
[19700102_00:42:16.351998]@0 last active wakeup source: eventpoll
[19700102_00:42:16.356927]@0 
[19700102_00:42:16.359589]@0 Freezing of tasks aborted after 0.020 seconds[19700102_00:42:16.366349]@0 
[19700102_00:42:16.368705]@0 Restarting tasks ... [19700102_00:42:16.379157]@0 done.
[19700102_00:42:16.382419]@0 PM: suspend exit 1970-01-01 16:42:16.382397642 UTC
[19700102_00:42:16.489083]@0 PM: suspend entry 1970-01-01 16:42:16.489058059 UTC
[19700102_00:42:16.495510]@0 PM: Syncing filesystems ... [19700102_00:42:16.507037]@0 done.
[19700102_00:42:16.513083]@0 Freezing user space processes ... 
[19700102_00:42:16.521917]@0 Error: returning -512 value
[19700102_00:42:16.532919]@0 (elapsed 0.014 seconds) [19700102_00:42:16.536566]@0 done.[19700102_00:42:16.539498]@0 
[19700102_00:42:16.542678]@0 Freezing remaining freezable tasks ... [19700102_00:42:16.553953]@0 (elapsed 0.005 seconds) [19700102_00:42:16.557592]@0 done.[19700102_00:42:16.560808]@0 
[19700102_00:42:16.563242]@0 Suspending console(s) (use no_console_suspend to debug)

===============================================suspend 模式不会重复进入.
2016年 02月 01日 星期一 14:07:55 CST

AT+EDFT=0,5
[19700102_00:56:50.559843]@0 blank on start
[19700102_00:56:50.559933]@0 fpc1020 soc:fpc_fpc1020: fb_notifier_callback screen on
[19700102_00:56:50.566941]@0 mdss_dsi_on start
[19700102_00:56:50.644775]@0 mdss_dsi_on end
[19700102_00:56:50.682391]@0 synaptics,s3320: synaptics_ts_resume enter!			唤醒
[19700102_00:56:50.682538]@0 synaptics,s3320: synaptics_ts_resume:normal end!
[19700102_00:56:50.685041]@0 blank on end
[19700102_00:56:50.741494]@0 mdss_dsi_post_panel_on:-
[19700102_00:56:50.746365]@0 --------backlight level = 100---------
OK[19700102_00:56:50.763576]@0 FTM: at_lcd_backlight_on - OK

[19700102_00:56:50.950581]@0 synaptics,s3320: synaptics_mode_change: set TP to mode[0x80]



AT+ESLP=1
[19700102_00:57:02.768010]@0 blank off start
[19700102_00:57:02.768097]@0 fpc1020 soc:fpc_fpc1020: fb_notifier_callback screen off
[19700102_00:57:02.768395]@0 synaptics,s3320: synaptics_ts_suspend enter			suspend
[19700102_00:57:02.772770]@0 synaptics,s3320: synaptics_mode_change: set TP to mode[0x1]
[19700102_00:57:02.773966]@0 synaptics,s3320: synaptics_ts_suspend normal end
[19700102_00:57:02.774299]@0 --------backlight level = 0---------
[19700102_00:57:03.016618]@0 mdss_dsi_off start
[19700102_00:57:03.058438]@0 mdss_dsi_off end
[19700102_00:57:03.063750]@0 blank off end
OK[19700102_00:57:04.117839]@0 FTM: at_sleep_enable - OK

=================================================

性能优化:


t@RAIN:/ # dmesg -c                                                         
[20160202_14:56:44.707849]@0 mdss_dsi_off end
[20160202_14:56:44.711901]@2 blank off end
[20160202_14:56:44.764675]@0 i2c-msm-v2 75b6000.i2c: NACK: slave not responding, ensure its powered: msgs(n:1 cur:0 tx) bc(rx:0 tx:4) mode:FIFO slv_addr:0x28 MSTR_STS:0x0d1300c8 OPER:0x00000090
[20160202_14:56:44.764831]@2 pn544_dev_write : i2c_master_send returned -107
[20160202_14:56:45.056170]@1 hvdcpd: Couldnt read parallel input_current_limited rc = -2
[20160202_14:56:45.428621]@1 __hif_pci_suspend: Waiting for CE to finish access: 
[20160202_14:56:45.442447]@1 __hif_pci_suspend: Suspend completes for runtime pm in wow mode event:2 device_state:-65
[20160202_14:56:45.442496]@1 __hif_pci_suspend: Suspend completes for runtime pm
[20160202_14:56:45.474281]@1 msm_pcie_disable: PCIe: Assert the reset of endpoint of RC0.
[20160202_14:56:45.478846]@1 cnss: runtime suspend status: 0
[20160202_14:56:45.762344]@0 cnss_wlan_pci 0000:01:00.0: Refused to change power state, currently in D3
[20160202_14:56:45.763125]@0 msm_pcie_enable: PCIe: Assert the reset of endpoint of RC0.
[20160202_14:56:45.768148]@0 msm_pcie_enable: PCIe RC0 PHY is ready!
[20160202_14:56:45.778620]@0 msm_pcie_enable: PCIe: Release the reset of endpoint of RC0.
[20160202_14:56:45.806799]@0 msm_pcie_enable: PCIe RC0 link initialized
[20160202_14:56:45.822498]@0 cnss_wlan_pci 0000:01:00.0: enabling device (0000 -> 0002)
[20160202_14:56:45.836556]@0 wlan: [0:F :WDA] WOW wakeup host event received (reason: PATTERN_MATCH_FOUND(9)) for vdev 0
[20160202_14:56:45.837521]@0 __hif_pci_resume: Resume completes for runtime pm in wow mode
[20160202_14:56:45.837628]@0 cnss: runtime resume status: 0
[20160202_14:56:45.837830]@0 hif_pci_pm_work: Resume HTT & WMI Service in runtime_pm state 1
[20160202_14:56:46.349136]@1 __hif_pci_suspend: Waiting for CE to finish access: 
[20160202_14:56:46.362417]@1 __hif_pci_suspend: Suspend completes for runtime pm in wow mode event:2 device_state:-65
[20160202_14:56:46.362452]@1 __hif_pci_suspend: Suspend completes for runtime pm
[20160202_14:56:46.393785]@1 msm_pcie_disable: PCIe: Assert the reset of endpoint of RC0.
[20160202_14:56:46.399409]@1 cnss: runtime suspend status: 0
[20160202_14:56:46.464736]@0 Power-Key DOWN
[20160202_14:56:46.485650]@0 blank on start
[20160202_14:56:46.485676]@0 fpc1020 soc:fpc_fpc1020: fb_notifier_callback screen on
[20160202_14:56:46.489830]@1 fpc1020 soc:fpc_fpc1020: fpc1020_irq_handler
[20160202_14:56:46.492853]@0 mdss_dsi_on start
[20160202_14:56:46.494938]@2 fpc1020 soc:fpc_fpc1020: fpc1020_irq_handler
[20160202_14:56:46.501876]@1 fpc1020 soc:fpc_fpc1020: fpc1020_irq_handler
[20160202_14:56:46.561468]@0 mdss_dsi_on end
[20160202_14:56:46.562598]@0 cnss_wlan_pci 0000:01:00.0: Refused to change power state, currently in D3
[20160202_14:56:46.562865]@0 msm_pcie_enable: PCIe: Assert the reset of endpoint of RC0.
[20160202_14:56:46.568661]@0 i2c-msm-v2 75b6000.i2c: NACK: slave not responding, ensure its powered: msgs(n:1 cur:0 tx) bc(rx:0 tx:4) mode:FIFO slv_addr:0x28 MSTR_STS:0x0d1300c8 OPER:0x00000090
[20160202_14:56:46.568784]@3 pn544_dev_write : i2c_master_send returned -107
[20160202_14:56:46.570266]@0 msm_pcie_enable: PCIe RC0 PHY is ready!
[20160202_14:56:46.580693]@0 msm_pcie_enable: PCIe: Release the reset of endpoint of RC0.
[20160202_14:56:46.596747]@3 synaptics,s3320: synaptics_ts_resume enter!				唤醒.    596...//fb->call-->resume-->work+ 5ms --> 进入到speedup_synaptics_resume
[20160202_14:56:46.596803]@3 synaptics,s3320: synaptics_ts_resume:normal end!				调度队列.596...//resume完等调度到 speedup_synaptics_resume.
[20160202_14:56:46.597126]@3 blank on end
[20160202_14:56:46.609842]@0 msm_pcie_enable: PCIe RC0 link initialized
[20160202_14:56:46.631952]@0 Power-Key UP
[20160202_14:56:46.632216]@0 cnss_wlan_pci 0000:01:00.0: enabling device (0000 -> 0002)
[20160202_14:56:46.640157]@0 wlan: [0:F :WDA] WOW wakeup host event received (reason: PATTERN_MATCH_FOUND(9)) for vdev 0
[20160202_14:56:46.640441]@0 __hif_pci_resume: Resume completes for runtime pm in wow mode
[20160202_14:56:46.640470]@0 cnss: runtime resume status: 0
[20160202_14:56:46.640513]@0 hif_pci_pm_work: Resume HTT & WMI Service in runtime_pm state 1
[20160202_14:56:46.641931]@1 mdss_dsi_post_panel_on:-
[20160202_14:56:46.642033]@1 --------backlight level = 29---------					屏幕亮
[20160202_14:56:46.843218]@2 synaptics,s3320: synaptics_mode_change: set TP to mode[0x80]		tp模式切换。出现不灵.time:843218..//调度到队列==>tpd_power返回，mode设置ok 触摸屏 normal 
[20160202_14:56:49.567628]@0 wlan: [8884:E :WDA]  scan complete - scan_id a0b6, vdev_id 0
[20160202_14:56:49.572539]@0 wlan: [2060:E :SME] Found 44 BSS, statusCode 0
[20160202_14:56:50.168854]@0 __hif_pci_suspend: Suspend completes for runtime pm in wow mode event:2 device_state:-65
[20160202_14:56:50.168906]@0 __hif_pci_suspend: Suspend completes for runtime pm
[20160202_14:56:50.204584]@0 msm_pcie_disable: PCIe: Assert the reset of endpoint of RC0.
[20160202_14:56:50.208263]@0 cnss: runtime suspend status: 0
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # 	//time: 843-596=246ms

msleep ==> usleep_range 后测试.

root@RAIN:/ # 
root@RAIN:/ # dmesg -c                                                         
[20160202_15:21:32.554185]@0 Power-Key DOWN
[20160202_15:21:32.602278]@2 blank on start
[20160202_15:21:32.602334]@2 fpc1020 soc:fpc_fpc1020: fb_notifier_callback screen on
[20160202_15:21:32.630915]@0 mdss_dsi_on start
[20160202_15:21:32.670459]@0 Power-Key UP
[20160202_15:21:32.682658]@3 mdss_dsi_on end
[20160202_15:21:32.727152]@3 synaptics,s3320: synaptics_ts_resume enter!				//step1: 32.727152  
[20160202_15:21:32.727281]@3 synaptics,s3320: synaptics_ts_resume:normal end!
[20160202_15:21:32.730986]@3 blank on end
[20160202_15:21:32.735050]@3 synaptics,s3320: speedup_synaptics_resume work enter tims			//step2: 32.735050
[20160202_15:21:32.785531]@1 mdss_dsi_post_panel_on:-
[20160202_15:21:32.827570]@0 i2c-msm-v2 75b6000.i2c: NACK: slave not responding, ensure its powered: msgs(n:1 cur:0 tx) bc(rx:0 tx:4) mode:FIFO slv_addr:0x28 MSTR_STS:0x0d1300c8 OPER:0x00000090
[20160202_15:21:32.827829]@2 pn544_dev_write : i2c_master_send returned -107
[20160202_15:21:32.859748]@0 --------backlight level = 49---------
[20160202_15:21:32.987146]@3 synaptics,s3320: synaptics_mode_change: set TP to mode[0x80]		//step3: 32.987146
root@RAIN:/ # 												//ret: t=987146-735050 = 252096  
root@RAIN:/ # 
root@RAIN:/ # dmesg -c                                                         
[20160202_15:21:34.301323]@0 binder: 3426:3426 transaction failed 29201, size 0-0
[20160202_15:21:34.302881]@2 type=1400 audit(1454397694.290:513): avc: denied { call } for pid=3426 comm="service" scontext=u:r:system_app:s0 tcontext=u:r:fingerprintd:s0 tclass=binder permissive=0
[20160202_15:21:39.786679]@0 Power-Key DOWN
[20160202_15:21:39.945048]@0 Power-Key UP
[20160202_15:21:40.530560]@0 --------backlight level = 0---------
[20160202_15:21:40.559993]@2 blank off start
[20160202_15:21:40.560023]@2 fpc1020 soc:fpc_fpc1020: fb_notifier_callback screen off
[20160202_15:21:40.560046]@2 synaptics,s3320: synaptics_ts_suspend enter
[20160202_15:21:40.574730]@2 synaptics,s3320: synaptics_mode_change: set TP to mode[0x1]
[20160202_15:21:40.576660]@2 synaptics,s3320: synaptics_ts_suspend normal end
[20160202_15:21:40.799101]@2 mdss_dsi_off start
[20160202_15:21:40.829563]@2 mdss_dsi_off end
[20160202_15:21:40.843061]@1 blank off end
[20160202_15:21:41.023284]@0 i2c-msm-v2 75b6000.i2c: NACK: slave not responding, ensure its powered: msgs(n:1 cur:0 tx) bc(rx:0 tx:4) mode:FIFO slv_addr:0x28 MSTR_STS:0x0d1300c8 OPER:0x00000090
[20160202_15:21:41.023428]@0 pn544_dev_write : i2c_master_send returned -107
[20160202_15:21:41.702084]@0 Power-Key DOWN
[20160202_15:21:41.746296]@3 blank on start
[20160202_15:21:41.746350]@3 fpc1020 soc:fpc_fpc1020: fb_notifier_callback screen on
[20160202_15:21:41.789098]@1 mdss_dsi_on start
[20160202_15:21:41.839606]@3 mdss_dsi_on end
[20160202_15:21:41.876852]@0 Power-Key UP
[20160202_15:21:41.879091]@2 synaptics,s3320: synaptics_ts_resume enter!
[20160202_15:21:41.879178]@2 synaptics,s3320: synaptics_ts_resume:normal end!
[20160202_15:21:41.880213]@2 blank on end
[20160202_15:21:41.884781]@0 synaptics,s3320: speedup_synaptics_resume work enter tims					//step2: 41.884781
[20160202_15:21:41.920382]@3 mdss_dsi_post_panel_on:-
[20160202_15:21:41.945907]@0 i2c-msm-v2 75b6000.i2c: NACK: slave not responding, ensure its powered: msgs(n:1 cur:0 tx) bc(rx:0 tx:4) mode:FIFO slv_addr:0x28 MSTR_STS:0x0d1300c8 OPER:0x00000090
[20160202_15:21:41.946182]@0 pn544_dev_write : i2c_master_send returned -107
[20160202_15:21:42.021056]@2 --------backlight level = 53---------
[20160202_15:21:42.140497]@3 synaptics,s3320: synaptics_mode_change: set TP to mode[0x80]				//step3: 42.140497
															//time:  255606 
root@RAIN:/ # 
root@RAIN:/ # 
root@RAIN:/ # 
