VCC = 3.3   -- NodeMCU on board 3.3v vcc
R2 = 10000  -- 10k ohm series resistor
adc_resolution = 1023 -- 10-bit adc

-- thermistor equation parameters
A = 0.001129148 
B = 0.000234125
C = 8.76741*10^-8 

-- initiating button
--buttonPin = 2
--gpio.mode(buttonPin, gpio.INPUT)
--gpio.write(buttonPin, gpio.LOW)


function ln(x)      --natural logarithm function for x>0 real values
    local y = (x-1)/(x+1)
    local sum = 1 
    local val = 1
    if(x == nil) then
        return 0
    end
-- we are using limited iterations to acquire reliable accuracy.
-- here its upto 10000 and increased by 2
    for i = 3, 10000, 2 do
        val = val*(y*y)
        sum = sum + (val/i)
    end
    return 2*y*sum
end



while true do

    local Vout, Rth, temperature
    local adc_value = adc.read(0)

    Vout = (adc_value * VCC) / adc_resolution
    Rth = (VCC * R2 / Vout) - R2
    
        temperature = (1 / (A + (B * ln(Rth)) + (C * (ln(Rth))^3)))   -- Temperature in kelvin
        temperature = temperature - 273.15  -- Temperature in degree celsius
        if (temperature != -273) {
        --pinMode(A0, OUTPUT)
       -- digitalWrite(A0, HIGH)
            print(string.format("Temperature = %0.3g °C",temperature));
        --print(digitalRead(A0))
            tmr.delay(100000);
        }
       
    

