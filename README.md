# MyCloud

MyCloud a **distributed cloud platform** using gRPC in C++ with following services:
1. **Mail(SMTP & POP3) service** with support for sending and receiving within its domain and also forwarding to external domains.
2. **Http server** to process front-end request from a browser, get appropriate data from the backend server and construct the http response.
3. **Drive service** with support for folder creation and uploading and downloading any kind file.This system was *fault tolerant* with quorum based causal replication done across multiple nodes and *loading balancing* done with dynamic distribution of users among different groups
