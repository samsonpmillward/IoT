buttonPin = 7
gpio.mode(buttonPin, gpio.INPUT)
gpio.write(buttonPin, gpio.LOW)
pushed = 0
dhtPin = 2
status, temp, humi, temp_dec, humi_dec = dht.read11(dhtPin)
mytimer = tmr.create()
mytimer:register(100,1, function()


if gpio.read(buttonPin)==1 then
 pushed = 1
 print("Button detected")
 if status == dht.OK then
--3 different status
--dht.OK, dht.ERROR_CHECKSUM, dht.ERROR_TIMEOUT
 print("DHT Temperature:"..temp..";".."Humidity:"..humi)
 pushed = 0
-- 2 dots are used for concatenation
    
elseif status == dht.ERROR_CHECKSUM then
 print( "DHT Checksum error." )
elseif status == dht.ERROR_TIMEOUT then
 print( "DHT timed out." )
end
end
end)
mytimer:start()
