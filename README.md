��#   M i n i G i t

 
MiniGit is a small model of Git, constructed the usage of C++.
It facilitates customers store exceptional variations in their files, cross lower back to antique changes, and paintings with branches — similar to actual Git, however simple.
#Why We Built It
This project was created as a final assignment for our Data Structures and Algorithms course. This project aims to have students implement a lightweight version of Git that tracks changes to files, supports commits, branching, merging, and log history — all from scratch, without using external version control libraries.
#Features requierd to include 
part 1-Initialization (init) – Initializes a new MiniGit repository
part 2-Add Files (add <filename>)– Stages files to be saved
part 3-Commit (commit -m <message>) – Saves a snapshot with message
part 4-View Log (log) – Shows commit history
part 5-Branching (branch <branch-name>) – Creates a new branch
part 6-Checkout (checkout <branch-name> or checkout <commit-hash>)
part 7-Merge (merge <branch-name>) – Merges another branch into the current one
part 8-(Optional) diff <commit1> <commit2> – Compares two commits
#Run commands
./minigit init
./minigit add hello.txt
./minigit commit -m "Initial version"
./minigit log
./minigit branch dev
./minigit merge dev

#Group Members
1,kidist Meseret-	init command	File I/O, 
                  Setup of .minigit/ directory	
                  File system structure (folders, objects)	
                  Project structure & README
2,Tsion Kindle -add <filename>	
                File hashing (custom or SHA-1)	
                Staging area logic	
                Object storage
3,Yadeni Getu- commit -m "msg"	
               Creating commit objects (timestamp, parent hash)	
               Link commits (DAG structure)	
               Write commit log
4,Sosina Zernichael	-log, branch, checkout	
                     Viewing history	
                     Switching between commits/branches	
                     Update HEAD
5, Dagmawi Tewodros Endale- merge <branch>
                            Lowest Common Ancestor (LCA) logic	
                            Conflict detection
                            
# Acknowledgment
Thanks to our lab assistant Mr. Habib for guiding us during the lab sessions.

# we learned 
We learned how Git works inside, how to work with file systems using C++, and how to manage file versions using hash functions and commit history.



