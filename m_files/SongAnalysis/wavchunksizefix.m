function wavchunksizefix( filename )

d = dir(filename);
fileSize = d.bytes;
fid=fopen(filename,'r+','l');
fseek(fid,4,-1);
fwrite(fid,fileSize-8,'uint32');
fseek(fid,40,-1);
fwrite(fid,fileSize-44,'uint32');
fclose(fid);