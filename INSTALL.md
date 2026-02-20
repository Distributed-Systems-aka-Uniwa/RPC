<p align="center">
  <img src="https://www.especial.gr/wp-content/uploads/2019/03/panepisthmio-dut-attikhs.png" alt="UNIWA" width="150"/>
</p>

<p align="center">
  <strong>UNIVERSITY OF WEST ATTICA</strong><br>
  SCHOOL OF ENGINEERING<br>
  DEPARTMENT OF COMPUTER ENGINEERING AND INFORMATICS
</p>

<p align="center">
  <a href="https://www.uniwa.gr" target="_blank">University of West Attica</a> ·
  <a href="https://ice.uniwa.gr" target="_blank">Department of Computer Engineering and Informatics</a>
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

<hr>

<p align="center">
  <strong>Supervision</strong>
</p>

<p align="center">
  Supervisor: Vasileios Mamalis, Professor
</p>
<p align="center">
  <a href="https://ice.uniwa.gr/en/emd_person/vassilios-mamalis/" target="_blank">UNIWA Profile</a>
</p>

<p align="center">
  Supervisor: Grammati Pantziou, Professor
</p>
<p align="center">
  <a href="https://ice.uniwa.gr/en/emd_person/grammati-pantziou/" target="_blank">UNIWA Profile</a> ·
  <a href="https://www.linkedin.com/in/grammati-pantziou-4731bb10a/" target="_blank">LinkedIn</a>
</p>

<p align="center">
  Co-supervisor: Doka Katerina, Senior Researcher<br>
</p>

<p align="center">
  <a href="http://www.cslab.ece.ntua.gr/~doka/" target="_blank">Academic Profile</a> ·
  <a href="https://www.linkedin.com/in/kdoka/" target="_blank">LinkedIn</a>
</p>

</hr>

---

<p align="center">
  Athens, May 2023
</p>

---

<p align="center">
  <img src="https://www.cdebyte.com/upload/image/20230730/6382635239819102581973620.png" width="250"/>
</p>

---

# INSTALL

## Mathematical Equations using Remote Procedure Call (RPC)

## Requirements

- **Operating System:** Linux or any Unix-like system that supports TCP sockets and ONC RPC.
- **Libraries:**
  - ONC RPC (Open Network Computing Remote Procedure Call)
  - Sockets (sys/socket.h)
- **Tools:** rpcgen (for generating RPC stubs), GCC (for compiling C programs).

---

## 1. Installation and Usage

### 1.1 Clone the Repository

Download the repository to your local machine:

```
git clone https://github.com/Distributed-Systems-aka-Uniwa/RPC.git
```

### 1.2 Compile and Setup

1. **Generate RPC Stubs**

   First, generate the necessary stubs for the RPC Server and RPC Client using the rpcgen utility. The `.x` file defines the interface for the three procedures:

   ```
   rpcgen -a -C rpc.x
   ```

   This will generate:

   `rpc.h`: Header file defining the structures and procedure prototypes.

   `rpc_clnt.c`: RPC Client stub.

   `rpc_svc.c`: RPC Server stub.

2. **Compile the RPC Server**

   Compile the RPC Server which will handle the computation of the requested tasks.

3. **Compile the Socket Server (also RPC Client)**

   The Socket Server (also RPC Client) forwards computation requests to the RPC Server and relays results back to the client.

4. **Automate the Compilation**

   There is a `Makefile` which helps you to automate the compilation of the `rpc_*.c files`:

   ```
   make
   ```

5. **Compile the Socket Client**

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

2. **Start the Socket Server**

   Next, start the Socket Server that acts as an intermediary between the Socket Clients and the RPC Server:

   ```
   ./rpc_client <port_number> <server_host>
   ```

3. **Start the Socket Client**

   Finally, start the Socket Client which will allow the user to input data and request computations:

   ```
   ./socket_client <port_number> <server_host>
   ```

---

## 2. Open the Documentation

1. Navigate to the `docs/` directory
2. Open the report corresponding to your preferred language:
   - English: `Remote-Procedure-Call.pdf`
   - Greek: `Απομακρυσμένη-Κλήση-Διαδικασίας.pdf`
