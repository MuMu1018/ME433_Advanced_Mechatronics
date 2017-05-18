function data = filters(port)

if ~isempty(instrfind)
    fclose(instrfind);
    delete(instrfind);
end

s = serial(port);
fopen(s);
fprintf(s,'r\n');

for i=1:99
	temp = fscanf(s,'%d %f');
    if(i>1)
        data(i-1)={temp};
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