wifi.sta.autoconnect(1)
--autoconnect
wifi.setmode(wifi.STATION)
station_cfg={}
station_cfg.ssid="uopiot2020"
station_cfg.pwd="2020a202"
station_cfg.save=true
wifi.sta.config(station_cfg)
--wifi.sta.connect()
--wifi.sta.disconnect()
--manual connect and disconnec