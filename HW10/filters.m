function data = filters(port)

if ~isempty(instrfind)
    fclose(instrfind);
    delete(instrfind);
end

s = serial(port);
fopen(s);
fprintf(s,'r\n');

for i=1:100
	temp = fscanf(s,'\r%d %f %f %f %f\r\n');
    if(i>1)
    data(i)={temp};
end
%cell2mat(data)

%plot(data(2,:))
%hold on
%plot(data(3,:))
%plot(data(4,:))
%plot(data(5,:))
%legend('raw','MAF','IIR','FIR')
%ylabel('z-acc');
%xlabel('Sample times');  

end