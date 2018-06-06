% Enter your MATLAB Code below
writeChId = <Channel ID>;  % replace with your channel number
writeKey = <Write Key>; % Replace with your channel write key
%[data,time] = thingSpeakRead(readChId,'Fields',2,'NumPoints',20);
us1 = thingSpeakRead(writeChId,'Fields',1,'NumPoints',50,'OutputFormat','table');
us2 = thingSpeakRead(writeChId,'Fields',2,'NumPoints',50,'OutputFormat','table');
laser = thingSpeakRead(writeChId,'Fields',6,'NumPoints',50,'OutputFormat','table');
us1
us2
laser
laser_data=laser.FieldLabel6
laser_data
counter=0
for i=2:length(laser_data)
    if(laser_data(i-1) == 1 && laser_data(i) == 0)
        counter=counter+1
    end
end
if(counter == 3)
    thingSpeakWrite(writeChId,'Fields',7,'Values',4,'WriteKey','WTPWUIP2YE2PMPNC');
else
    thingSpeakWrite(writeChId,'Fields',7,'Values',3,'WriteKey','WTPWUIP2YE2PMPNC');
end
