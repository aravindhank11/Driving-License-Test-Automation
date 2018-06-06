% Enter your MATLAB Code below
writeChId = <channel_id>;  % replace with your channel number
writeKey = <write Key>; % Replace with your channel write key
%[data,time] = thingSpeakRead(readChId,'Fields',2,'NumPoints',20);
table_start = thingSpeakRead(writeChId,'Fields',3,'NumPoints',50,'OutputFormat','table');
table_stop = thingSpeakRead(writeChId,'Fields',4,'NumPoints',50,'OutputFormat','table');
us1 = thingSpeakRead(writeChId,'Fields',1,'NumPoints',50,'OutputFormat','table');
us2 = thingSpeakRead(writeChId,'Fields',2,'NumPoints',50,'OutputFormat','table');
time2 = us2.Timestamps
data2 = us2.FieldLabel2
data3 = table_start.FieldLabel3
time3 = table_start.Timestamps
data4 = table_stop.FieldLabel4
time4 = table_stop.Timestamps
start_time = -1
for i=length(data3):-1:1
    if(data3(i) == 1)
        start_time = time3(i);
        fprintf('Start: %s\n',time3(i));
        break
    end
end
for i=length(data3):-1:1
    if(data3(i) == 2)
        stop_time = time3(i);
        fprintf('Stop: %s\n',time3(i));
        break
    end
end
data1 = us1.FieldLabel1
time1 = us1.Timestamps
us1
temp=0
for i=1:length(time1)
    if(time1(i) == start_time)
        while time1(i) ~= stop_time
            if(data1(i)>2500)
                fprintf('%s\n',time1(i));
                temp = 1
                break
            else
                fprintf('%s',data1(i));
                i=i+1
            end
        end
    end
end 
if(temp == 0)
    for i=1:length(time2)
        if(time2(i) == start_time)
            while time2(i) ~= stop_time
                if(data2(i)>2500)
                    fprintf('%s\n',time2(i));
                    temp = 1
                    break
                else
                    fprintf('%s',data2(i));
                    i=i+1
                end
            end
        end
    end
else
    fprintf("Failed");
end
if(temp == 1)
    thingSpeakWrite(writeChId,'Fields',3,'Values',3,'WriteKey','WTPWUIP2YE2PMPNC');
else
    thingSpeakWrite(writeChId,'Fields',3,'Values',4,'WriteKey','WTPWUIP2YE2PMPNC');
end
