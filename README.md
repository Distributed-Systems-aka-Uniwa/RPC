![Alt text](https://upload.wikimedia.org/wikipedia/commons/thumb/a/a5/Flag_of_the_United_Kingdom_%281-2%29.svg/255px-Flag_of_the_United_Kingdom_%281-2%29.svg.png)

# Concurrent Socket Server with ONC RPC Communication

For the requested Assignment, click the link:  
[Assignment](Assignment/)

For the Source Code, click the link:  
[Code](Code/)

For the detailed Documentation, click the link:  
[Documentation](Documentation/)

## Overview

This project involves creating a concurrent **socket server** using **TCP AF_INET (Internet Domain) sockets** in C. The server processes requests from clients to perform calculations based on two integer vectors and a real number. The computations are executed via **Remote Procedure Calls (RPC)** on a separate **RPC server**, which returns the results back to the client through the socket server.

## Course Information

- **Course**: [Distributed Systems](https://ice.uniwa.gr/education/undergraduate/courses/distributed-systems/)
- **Semester**: 6
- **Program of Study**: [UNIWA](https://www.uniwa.gr/)
- **Department**: [Informatics and Computer Engineering](https://ice.uniwa.gr/)
- **Lab Instructor**: [Doka Aikaterini](http://www.cslab.ece.ntua.gr/~doka/)
- **Academic Season**: 2022-2023

## Student Information

- **Name**: Athanasiou Vasileios Evangelos
- **Student ID**: 19390005
- **Status**: Undergraduate

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

![Alt text](https://upload.wikimedia.org/wikipedia/commons/thumb/5/5c/Flag_of_Greece.svg/255px-Flag_of_Greece.svg.png)

# Ταυτόχρονος Διακομιστής Sockets με Επικοινωνία ONC RPC

Για την ζητούμενη Άσκηση, κάντε κλικ στον σύνδεσμο:  
[Άσκηση](Assignment/)

Για τον Πηγαίο Κώδικα, κάντε κλικ στον σύνδεσμο:  
[Κώδικας](Code/)

Για την λεπτομερή Τεκμηρίωση, κάντε κλικ στον σύνδεσμο:  
[Τεκμηρίωση](Documentation/)

## Επισκόπηση

Αυτό το έργο περιλαμβάνει τη δημιουργία ενός ταυτόχρονου **διακομιστή sockets** χρησιμοποιώντας **TCP AF_INET (Internet Domain) sockets** σε C. Ο διακομιστής επεξεργάζεται αιτήματα από πελάτες για να εκτελέσει υπολογισμούς βάσει δύο ακέραιων διανυσμάτων και ενός πραγματικού αριθμού. Οι υπολογισμοί εκτελούνται μέσω **Κλήσεων Απομακρυσμένης Διαδικασίας (RPC)** σε έναν ξεχωριστό **RPC διακομιστή**, ο οποίος επιστρέφει τα αποτελέσματα πίσω στον πελάτη μέσω του διακομιστή sockets.

## Πληροφορίες Μαθήματος

- **Μάθημα**: [Κατανεμημένα Συστήματα](https://ice.uniwa.gr/education/undergraduate/courses/distributed-systems/)
- **Εξάμηνο**: 6
- **Πρόγραμμα Σπουδών**: [ΠΑΔΑ](https://www.uniwa.gr/)
- **Τμήμα**: [Μηχανικών Πληροφορικής και Υπολογιστών](https://ice.uniwa.gr/)
- **Διδάσκουσα**: [Δόκα Αικατερίνη](http://www.cslab.ece.ntua.gr/~doka/)
- **Ακαδημαϊκή Χρονιά**: 2022-2023

## Πληροφορίες Φοιτητή

- **Όνομα**: Αθανασίου Βασίλειος Ευάγγελος
- **Αριθμός Μητρώου**: 19390005
- **Κατάσταση**: Προπτυχιακός Φοιτητής

## Κύρια Χαρακτηριστικά

- **Ταυτόχρονος Διακομιστής**: Ο διακομιστής χειρίζεται ταυτόχρονα πολλά αιτήματα πελατών χρησιμοποιώντας διεργασίες παιδιών.
- **Επικοινωνία με Sockets TCP**: Οι πελάτες συνδέονται στον διακομιστή χρησιμοποιώντας TCP sockets για να στείλουν και να λάβουν δεδομένα.
- **ONC RPC**: Ο διακομιστής, λειτουργώντας ως RPC πελάτης, επικοινωνεί με έναν εξωτερικό RPC διακομιστή για να εκτελέσει τους απαιτούμενους υπολογισμούς.
- **Κλήσεις Απομακρυσμένης Διαδικασίας**: Ο διακομιστής χρησιμοποιεί τρεις ξεχωριστές λειτουργίες βασισμένες σε RPC για υπολογισμούς, ανάλογα με την επιλογή του χρήστη:
  1. **Εσωτερικό Γινόμενο Δύο Διανυσμάτων** (`X * Y`)
  2. **Μέση Τιμή Κάθε Διανύσματος** (`X̄`, `Ȳ`)
  3. **Γινόμενο r\*(X + Y)**

## Ροή Προγράμματος

1. **Πλευρά Πελάτη**:  
   - Ο χρήστης επιλέγει τον επιθυμητό υπολογισμό (εσωτερικό γινόμενο, μέση τιμή ή γινόμενο).
   - Ο πελάτης στέλνει τα απαιτούμενα δεδομένα (`n`, διανύσματα `X` και `Y`, και πραγματικό αριθμό `r`) στον διακομιστή sockets.
   - Ο πελάτης περιμένει το αποτέλεσμα από τον διακομιστή sockets, το οποίο επιστρέφεται μετά την επεξεργασία.

2. **Πλευρά Διακομιστή**:  
   - Ο διακομιστής δέχεται τη σύνδεση του πελάτη και λαμβάνει το αίτημα υπολογισμού.
   - Προωθεί τα δεδομένα στον RPC διακομιστή για επεξεργασία.
   - Ο διακομιστής λαμβάνει το υπολογισμένο αποτέλεσμα από τον RPC διακομιστή και το στέλνει πίσω στον πελάτη.

3. **RPC Διακομιστής**:  
   - Εκτελεί τον ζητούμενο υπολογισμό χρησιμοποιώντας τα δεδομένα που παρέχονται από τον διακομιστή sockets.

## Απαιτήσεις

- **Λειτουργικό Σύστημα:** Linux ή οποιοδήποτε Unix-like σύστημα που υποστηρίζει TCP sockets και ONC RPC.
- **Βιβλιοθήκες:**
    - ONC RPC (Open Network Computing Remote Procedure Call)
    - Sockets `(sys/socket.h)`
- **Εργαλεία:** `rpcgen` (για την παραγωγή RPC stubs), GCC (για τη μεταγλώττιση προγραμμάτων C).

## Εγκατάσταση και Χρήση

### 1. Κλωνοποιήστε το αποθετήριο
Κατεβάστε το αποθετήριο στον τοπικό σας υπολογιστή:
```
git clone https://github.com/Distributed-Systems-aka-Uniwa/RPC.git
```

### 2. Μεταγλώττιση και Setup
1. **Παραγωγή των RPC Stubs**

   Πρώτα, παράγετε τα απαραίτητα stubs για τον RPC Διακομιστή και τον RPC Πελάτη χρησιμοποιώντας το εργαλείο `rpcgen`. Το αρχείο `.x` ορίζει τη διεπαφή για τις τρεις διαδικασίες:
    ```
    rpcgen -a -C rpc.x
    ```
    Αυτό θα δημιουργήσει:
   
    `rpc.h`: Αρχείο κεφαλίδας που ορίζει τις δομές και τις υπογραφές διαδικασιών.

   `rpc_clnt.c`: Stub για τον RPC Πελάτη.

   `rpc_svc.c`: Stub για τον RPC Διακομιστή.
    
3. **Μεταγλώττιση του RPC Διακομιστή**

   Μεταγλωττίστε τον RPC Διακομιστή ο οποίος θα χειρίζεται τον υπολογισμό των ζητούμενων εργασιών.

5. **Μεταγλώττιση του Socket Διακομιστή (επίσης RPC Πελάτη)**

   Ο Socket Διακομιστής (επίσης RPC Πελάτης) προωθεί τα αιτήματα υπολογισμού στον RPC Διακομιστή και επιστρέφει τα αποτελέσματα πίσω στον πελάτη.

7. **Αυτοματοποίηση της Μεταγλώττισης**

   Υπάρχει ένα `Makefile` που βοηθά στην αυτοματοποίηση της μεταγλώττισης των `rpc_*.c files`:
    ```
    make
    ```

9. **Μεταγλώττιση του Socket Πελάτη**

   Ο Socket Πελάτης επιτρέπει στον χρήστη να επιλέξει μια εργασία υπολογισμού και να παρέχει τα απαραίτητα δεδομένα:
    ```
    gcc -o socket_client socket_client.c
    ```

### 3. Εκτέλεση
1. **Εκκίνηση του RPC Διακομιστή**

   Πρώτα, ξεκινήστε τον RPC Διακομιστή που θα χειρίζεται τους απομακρυσμένους υπολογισμούς:
    ```
    ./rpc_server
    ```
3. **Εκκίνηση του Socket Διακομιστή**

   Στη συνέχεια, ξεκινήστε τον Socket Διακομιστή που λειτουργεί ως μεσολαβητής μεταξύ των Socket Πελατών και του RPC Διακομιστή:
    ```
    ./rpc_client <port_number> <server_host>
    ```
5. **Εκκίνηση του Socket Πελάτη**

   Τέλος, ξεκινήστε τον Socket Πελάτη που θα επιτρέπει στον χρήστη να εισάγει δεδομένα και να ζητά υπολογισμούς:
    ```
    ./socket_client <port_number> <server_host>
    ```
