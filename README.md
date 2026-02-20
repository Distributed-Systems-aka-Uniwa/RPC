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

# README

## Mathematical Equations using Remote Procedure Call (RPC)

This project involves creating a concurrent **socket server** using **TCP AF_INET (Internet Domain) sockets** in C. The server processes requests from clients to perform calculations based on two integer vectors and a real number. The computations are executed via **Remote Procedure Calls (RPC)** on a separate **RPC server**, which returns the results back to the client through the socket server.

---

## Table of Contents

| Section | Folder / File                              | Description                                   |
| ------: | ------------------------------------------ | --------------------------------------------- |
|       1 | `assign/`                                  | Assignment material                           |
|     1.1 | `assign/DS-LAB-ASK-1-2022-23.pdf`          | Laboratory assignment description (English)   |
|     1.2 | `assign/ΚΣ-ΕΡΓΑΣΤΗΡΙΟ-ΑΣΚ-1-2022-23.pdf`   | Περιγραφή εργαστηριακής άσκησης (Greek)       |
|       2 | `docs/`                                    | Theoretical documentation                     |
|     2.1 | `docs/Remote-Procedure-Call.pdf`           | Remote Procedure Call (RPC) theory (English)  |
|     2.2 | `docs/Απομακρυσμένη-Κλήση-Διαδικασίας.pdf` | Απομακρυσμένη Κλήση Διαδικασίας – RPC (Greek) |
|       3 | `src/`                                     | Source code implementation                    |
|     3.1 | `src/Makefile`                             | Build automation file                         |
|     3.2 | `src/rpc.x`                                | RPC interface definition (XDR specification)  |
|     3.3 | `src/rpc.h`                                | RPC shared header file                        |
|     3.4 | `src/rpc_xdr.c`                            | XDR data serialization/deserialization        |
|     3.5 | `src/rpc_server.c`                         | RPC server implementation                     |
|     3.6 | `src/rpc_svc.c`                            | RPC service-side stub code                    |
|     3.7 | `src/rpc_client.c`                         | RPC client implementation                     |
|     3.8 | `src/rpc_clnt.c`                           | RPC client-side stub code                     |
|     3.9 | `src/socket_client.c`                      | Low-level socket client implementation        |
|       4 | `README.md`                                | Project documentation                         |
|       5 | `INSTALL.md`                               | Usage instructions                            |

---

## 1. Key Features

- **Concurrent Server**: The server handles multiple client requests concurrently using forked child processes.
- **TCP Socket Communication**: The clients connect to the server using TCP sockets to send and receive data.
- **ONC RPC**: The server, acting as an RPC client, communicates with an external RPC server to perform the required calculations.
- **Remote Procedure Calls**: The server uses three distinct RPC-based functions for calculations, depending on the user's choice:
  1. **Inner Product of Two Vectors** (`X * Y`)
  2. **Average Value of Each Vector** (`X̄`, `Ȳ`)
  3. **Product r\*(X + Y)**

---

## 2. Program Workflow

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
