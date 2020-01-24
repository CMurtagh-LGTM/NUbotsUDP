clear ProtobufEncode
clear ProtobufDecode
mex -I/usr/local/include -L/usr/local/lib/ -lprotobuf ProtobufEncode.cpp Vector.pb.cc
mex -I/usr/local/include -L/usr/local/lib/ -lprotobuf ProtobufDecode.cpp Vector.pb.cc