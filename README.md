# SocialNet Simulator

SocialNet is a command-line social network backend simulator developed for the **COL106: Data Structures** course. The system manages users, friendships, and content using advanced data structures including **AVL Trees** for post management and **Graphs** for representing the social network.

---

## 🚀 Features

### Social Network Operations

* 
**User Management**: Add new users to the network.


* 
**Friendship Management**: Establish bidirectional friendships between users.


* 
**Friend Listings**: View an alphabetically sorted list of any user's friends.


* 
**Friend Suggestions**: Recommends "friends of a friend" based on mutual connection counts.


* 
**Degrees of Separation**: Calculate the shortest friendship path between two users using graph traversal.



### User Content Operations

* 
**Post Creation**: Users can create posts with text content.


* 
**Chronological Feed**: Retrieve the  most recent posts from a user in reverse chronological order using an AVL Tree.



---

## 🛠️ System Architecture

The simulator is built from scratch without using standard library containers for the core logic (except for `unordered_map` to map usernames to vertices):

* 
**Graph**: Represents users as vertices and friendships as undirected edges.


* 
**AVL Tree (Posts)**: Stores user posts sorted by creation timestamp for efficient retrieval.


* 
**AVL Tree (Friends)**: Maintains a user's friend list in alphabetical order.



---

## 💻 Technical Requirements

* **Language**: C++
* **Compiler**: `g++` (supports C++11 or higher)
* 
**Input**: Interactive command-line interface (stdin).



---

## 📖 Command Reference

### User & Friendship Commands

| Command | Description |
| --- | --- |
| `ADD USER <username>` | Adds a new user to the network.

 |
| `ADD FRIEND <u1> <u2>` | Creates a bidirectional friendship.

 |
| `LIST FRIENDS <username>` | Lists all friends alphabetically.

 |
| `SUGGEST FRIENDS <u1> <N>` | Suggests up to  friends based on mutuals.

 |
| `DEGREES OF SEPARATION <u1> <u2>` | Finds the shortest friendship path.

 |

### Content Commands

| Command | Description |
| --- | --- |
| `ADD POST <username> "<content>"` | Adds a post for the specified user.

 |
| `OUTPUT POSTS <username> <N>` | Shows  latest posts (use -1 for all).

 |

### System Commands

* **HELP**: Displays the command reference.
* **CLEAR**: Clears the terminal screen.
* **EXIT**: Gracefully closes the simulator.

> 
> **Note:** Usernames and commands are case-insensitive. Post content must be enclosed in double quotes.
> 
> 

---

## 🛠️ Installation & Usage

1. **Compile the code**:
```bash
g++ -o socialnet main.cpp

```


2. **Run the simulator**:
```bash
./socialnet

```


3. **Example Session**:
```text
socialnet>> ADD USER Alice
socialnet>> ADD USER Bob
socialnet>> ADD FRIEND Alice Bob
socialnet>> ADD POST Alice "My first post!"
socialnet>> OUTPUT POSTS Alice 1

```



---

## 📝 Submission & Credits

* 
**Deadline**: November 05, 15:00 IST.


* **Developer**: Shivanshu Aryan (2024CS10237).
