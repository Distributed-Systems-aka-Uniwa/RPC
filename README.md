<p align="center">
  <img src="https://www.especial.gr/wp-content/uploads/2019/03/panepisthmio-dut-attikhs.png" alt="UNIWA" width="150"/>
</p>

<p align="center">
  <strong>UNIVERSITY OF WEST ATTICA</strong><br>
  SCHOOL OF ENGINEERING<br>
  DEPARTMENT OF COMPUTER ENGINEERING AND INFORMATICS
</p>

---

<p align="center">
  <strong>Distributed Systems</strong>
</p>

<h1 align="center">
  Mathematical Equations using Remote Procedure Call (RPC)
</h1>

<p align="center">
  <strong>Vasileios Evangelos Athanasiou</strong><br>
  Student ID: 19390005
</p>

<p align="center">
  <a href="https://github.com/Ath21" target="_blank">GitHub</a> ·
  <a href="https://www.linkedin.com/in/vasilis-athanasiou-7036b53a4/" target="_blank">LinkedIn</a>
</p>

<p align="center">
  Supervisor: Doka Katerina, Senior Researcher<br>
</p>

<p align="center">
  <a href="http://www.cslab.ece.ntua.gr/~doka/" target="_blank">UNIWA Profile</a> ·
  <a href="https://www.linkedin.com/in/kdoka/" target="_blank">LinkedIn</a>
</p>

<p align="center">
  Athens, May 2023
</p>

---

## Project Overview

This project involves creating a concurrent **socket server** using **TCP AF_INET (Internet Domain) sockets** in C. The server processes requests from clients to perform calculations based on two integer vectors and a real number. The computations are executed via **Remote Procedure Calls (RPC)** on a separate **RPC server**, which returns the results back to the client through the socket server.

---

## Table of Contents


| Section | Folder / File | Description |
|------:|---------------|-------------|
| 1 | `assign/` | Assignment material |
| 1.1 | `assign/DS-LAB-ASK-1-2022-23.pdf` | Laboratory assignment description (English) |
| 1.2 | `assign/ΚΣ-ΕΡΓΑΣΤΗΡΙΟ-ΑΣΚ-1-2022-23.pdf` | Περιγραφή εργαστηριακής άσκησης (Greek) |
| 2 | `docs/` | Theoretical documentation |
| 2.1 | `docs/Remote-Procedure-Call.pdf` | Remote Procedure Call (RPC) theory (English) |
| 2.2 | `docs/Απομακρυσμένη-Κλήση-Διαδικασίας.pdf` | Απομακρυσμένη Κλήση Διαδικασίας – RPC (Greek) |
| 3 | `src/` | Source code implementation |
| 3.1 | `src/Makefile` | Build automation file |
| 3.2 | `src/rpc.x` | RPC interface definition (XDR specification) |
| 3.3 | `src/rpc.h` | RPC shared header file |
| 3.4 | `src/rpc_xdr.c` | XDR data serialization/deserialization |
| 3.5 | `src/rpc_server.c` | RPC server implementation |
| 3.6 | `src/rpc_svc.c` | RPC service-side stub code |
| 3.7 | `src/rpc_client.c` | RPC client implementation |
| 3.8 | `src/rpc_clnt.c` | RPC client-side stub code |
| 3.9 | `src/socket_client.c` | Low-level socket client implementation |
| 4 | `README.md` | Repository overview and usage instructions |


---

## Key Features

- **Concurrent Server**: The server handles multiple client requests concurrently using forked child processes.
- **TCP Socket Communication**: The clients connect to the server using TCP sockets to send and receive data.
- **ONC RPC**: The server, acting as an RPC client, communicates with an external RPC server to perform the required calculations.
- **Remote Procedure Calls**: The server uses three distinct RPC-based functions for calculations, depending on the user's choice:
  1. **Inner Product of Two Vectors** (`X * Y`)
  2. **Average Value of Each Vector** (`X̄`, `Ȳ`)
  3. **Product r\*(X + Y)**

## Program Workflow

1. **Client Side**:  
   - The user selects the desired computation (inner product, average, or product).
   - The client sends the required data (`n`, vectors `X` and `Y`, and real number `r`) to the socket server.
   - The client waits for the result from the socket server, which is returned after processing.

2. **Server Side**:  
   - The server accepts the client's connection and receives the computation request.
   - It forwards the data to the RPC server for processing.
   - The server receives the computed result from the RPC server and sends it back to the client.

3. **RPC Server**:  
   - It performs the requested computation using the data provided by the socket server.

## Requirements

- **Operating System:** Linux or any Unix-like system that supports TCP sockets and ONC RPC.
- **Libraries:**
    - ONC RPC (Open Network Computing Remote Procedure Call)
    - Sockets (sys/socket.h)
- **Tools:** rpcgen (for generating RPC stubs), GCC (for compiling C programs).

## Installation and Usage

### 1. Clone the Repository
Download the repository to your local machine:
```
git clone https://github.com/Distributed-Systems-aka-Uniwa/RPC.git
```
### 2. Compile and Setup
1. **Generate RPC Stubs**

   First, generate the necessary stubs for the RPC Server and RPC Client using the rpcgen utility. The `.x` file defines the interface for the three procedures:
    ```
    rpcgen -a -C rpc.x
    ```
    This will generate:
   
   `rpc.h`: Header file defining the structures and procedure prototypes.

   `rpc_clnt.c`: RPC Client stub.

   `rpc_svc.c`: RPC Server stub.
    
3. **Compile the RPC Server**

   Compile the RPC Server which will handle the computation of the requested tasks.

4. **Compile the Socket Server (also RPC Client)**

   The Socket Server (also RPC Client) forwards computation requests to the RPC Server and relays results back to the client.

6. **Automate the Compilation**

   There is a `Makefile` which helps you to automate the compilation of the `rpc_*.c files`:
    ```
    make
    ```

8. **Compile the Socket Client**

   The Socket Client allows the user to select a computation task and provides the necessary data:
    ```
    gcc -o socket_client socket_client.c
    ```

### 3. Execute
1. **Start the RPC Server**

   First, start the RPC Server that will handle the remote computations:
    ```
    ./rpc_server
    ```
3. **Start the Socket Server**

   Next, start the Socket Server that acts as an intermediary between the Socket Clients and the RPC Server:
    ```
    ./rpc_client <port_number> <server_host>
    ```
5. **Start the Socket Client**

   Finally, start the Socket Client which will allow the user to input data and request computations:
    ```
    ./socket_client <port_number> <server_host>
    ```

---

## Open the Documentation
1. Navigate to the `docs/` directory
2. Open the report corresponding to your preferred language:
    - English: `Remote-Procedure-Call.pdf`
    - Greek: `Απομακρυσμένη-Κλήση-Διαδικασίας.pdf`