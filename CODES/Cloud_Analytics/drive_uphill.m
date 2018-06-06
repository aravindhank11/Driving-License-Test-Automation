% Enter your MATLAB Code below
writeChId = <Channel ID>;  % replace with your channel number
writeKey = <Write Key>; % Replace with your channel write key
%[data,time] = thingSpeakRead(readChId,'Fields',2,'NumPoints',20);
table_start = thingSpeakRead(writeChId,'Fields',3,'NumPoints',50,'OutputFormat','table');
input = thingSpeakRead(writeChId,'Fields',4,'NumPoints',50,'OutputFormat','table');
input
inputdata=input.FieldLabel4
for i=2:length(inputdata)
    if(inputdata(i)>17)
        continue;
    else
        if(isnan(inputdata(i)) == 0)
            if(inputdata(i-1)-inputdata(i) <= 3)
                fprintf("Climbing\n");      
            else
                if(inputdata(i-1)>20)
                    continue
                end
            end
            thingSpeakWrite(writeChId,'Fields',5,'Values',3,'WriteKey','WTPWUIP2YE2PMPNC');
            break;
        end
    end
end
if(i == length(inputdata))
    thingSpeakWrite(writeChId,'Fields',5,'Values',4,'WriteKey','WTPWUIP2YE2PMPNC');
end
