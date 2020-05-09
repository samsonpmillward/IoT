mytimer=tmr.create()
mytimer:register(2000,tmr.ALARM_AUTO,function()
dhtPin = 2
status, temp, humi, temp_dec, humi_dec = dht.read11(dhtPin)
if status == dht.OK then
--3 different status
--dht.OK, dht.ERROR_CHECKSUM, dht.ERROR_TIMEOUT
 print("DHT Temperature:"..temp..";".."Humidity:"..humi)
-- 2 dots are used for concatenation
elseif status == dht.ERROR_CHECKSUM then
 print( "DHT Checksum error." )
elseif status == dht.ERROR_TIMEOUT then
 print( "DHT timed out." )
tmr.delay(1000)
end
end)
mytimer:start()