% LabComp
% This is a vector approach to quantization. We can choose the vector 
% size but the number of codewords generated is not under our control. 
% The measure used is maximum absolute difference between the best codeword 
% and the vector chunk. The Per Character Distortion is calculated for 
% each character in the vector with the codeword. A restriction is 
% placed on this max. absolute difference. 
% A data block is inducted into the codebook if it does not satisfy the 
% criterion with any existing codeword. The codeword used to encode the 
% considered data block is the one which offers the lowest maximum PCD
% (Per character distortion), where max PCD refers to the highest
% PCD occuring when using a codeword to represent a data vector.

f = fopen('QualVals.txt','r'); %Your file containing Quality Values
seq = fscanf(f,'%c');
vecsize = 5;
maxdist = 5;
dict = [];
quantseq = seq; %say initially
n = length(seq)/vecsize;
for i=1:n
    v = seq(1,((i-1)*vecsize+1):(i*vecsize));   %Consider the i-th data block
    d = [];
    ind = 0;
    if length(dict)<1   
        dict = [dict v];    % add the first data block to the dictionary
        quantseq(1,((i-1)*vecsize+1):(i*vecsize)) = seq(1,((i-1)*vecsize+1):(i*vecsize));
    else
        for j=1:(length(dict)/vecsize)
        temp = abs(v-dict(1,((j-1)*vecsize+1):(j*vecsize)));
        m = max(temp);
        if(m<maxdist)
            ind = j;
            break;
        end
        %d = [d m];
        end
        %[l,ind] = min(d);
        
        %Encoding the the sequence 
        
        if  (ind==0)
            dict = [dict v];
            quantseq(1,((i-1)*vecsize+1):(i*vecsize)) = seq(1,((i-1)*vecsize+1):(i*vecsize));
        else
            quantseq(1,((i-1)*vecsize+1):(i*vecsize)) = dict(1,((ind-1)*vecsize+1):(ind*vecsize));
        end
    end
end
% writing the quantized sequence data into a file to compress using bzip2
f = fopen('QuantizedQvals.txt','w');
fwrite(f,quantseq);
fclose(f);
    
