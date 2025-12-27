# SocialNet Simulator

SocialNet is a command-line backend simulator for a social network, developed as part of the **COL106: Data Structures** course. The system manages users, friendships, and content using custom-implemented data structures to ensure efficiency in a networked environment.

---

## 🚀 Features

### Social Network Operations

* 
**User Management**: Add new users to the network.


* 
**Friendship Management**: Establish bidirectional friendships between existing users.


* 
**Friend Listings**: Retrieve an alphabetically sorted list of a user's friends.


* 
**Friend Suggestions**: Recommends "friends of a friend" ranked by mutual connection counts.


* 
**Degrees of Separation**: Calculate the shortest path between two users using Breadth-First Search (BFS).



### User Content Operations

* 
**Post Creation**: Users can create posts with text content, automatically timestamped.


* 
**Chronological Feed**: Retrieve the  most recent posts from a user in reverse chronological order.



---

## 🛠️ System Architecture & Design Decisions

The project strictly avoids standard library containers for core logic, implementing fundamental data structures from scratch.

### Data Structures

* **Graph**: Users are represented as vertices, and friendships are undirected edges. This allows for efficient traversal for "Degrees of Separation".


* 
**AVL Tree (Posts)**: To ensure that retrieving the  latest posts is efficient, posts are stored in a self-balancing AVL tree keyed by timestamp.


* **AVL Tree (Friends)**: While the graph manages connections, each user maintains an internal AVL tree of friends to allow for  insertion and alphabetical retrieval.
* 
**Hash Map**: A `std::unordered_map` is used to map username strings to User objects for  average-case lookup.



### Complexity Analysis

| Operation | Data Structure | Time Complexity |
| --- | --- | --- |
| **Add User** | Hash Map |  average |
| **Add Friend** | AVL Tree |  where  is number of friends |
| **List Friends** | AVL Tree |  (In-order traversal) |
| **Add Post** | AVL Tree |  where  is number of posts |
| **Output  Posts** | AVL Tree |  |
| **Separation** | Graph (BFS) |  where  = users,  = friendships |

---

## 📖 Command Reference

The simulator accepts commands via `stdin` at runtime. Commands and usernames are case-insensitive.

| Command | Usage |
| --- | --- |
| **ADD USER** | `ADD USER <username>` |
| **ADD FRIEND** | `ADD FRIEND <user1> <user2>` |
| **LIST FRIENDS** | `LIST FRIENDS <username>` |
| **SUGGEST FRIENDS** | `SUGGEST FRIENDS <username> <N>` |
| **DEGREES OF SEPARATION** | `DEGREES OF SEPARATION <user1> <user2>` |
| **ADD POST** | `ADD POST <username> "<content>"` |
| **OUTPUT POSTS** | `OUTPUT POSTS <username> <N>` |
| **HELP** | Displays the command reference. |
| **EXIT** | Terminates the simulator. |

---

## 💻 Installation & Execution

### Prerequisites

* A C++ compiler supporting **C++17** (e.g., `g++`).

### Compilation

You can compile manually or use the provided shell script:

```bash
# Using the shell script
chmod +x compile.sh
./compile.sh

# Manual compilation
g++ -std=c++17 -O2 -Wall -Wextra -o socialnet main.cpp

```

### Running the Simulator

Once compiled, run the executable:

```bash
./socialnet

```

---

## 📝 Submission & Credits

* 
**Deadline**: November 05, 15:00 IST.


* **Developer**: Shivanshu Aryan (2024CS10237).
