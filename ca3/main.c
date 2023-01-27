#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>

struct UserStruct {
	char *user;
	char *password;
};

struct PostStruct {
	char *user;
	int post_id;
	int like;
	char *post;
};

// A Post linked list node
struct PostNode {
	PostStruct data;
	struct PostNode *next;
};

// A User linked list node
struct UserNode {
	UserStruct data;
	struct UserNode *next;
};


void pushPost(struct PostNode** head_ref, PostStruct new_data) {
	/* 1. allocate node */
	struct PostNode* new_node = (struct PostNode*) malloc(sizeof(struct PostNode));

	/* 2. put in the data  */
	new_node->data  = new_data;

	/* 3. Make next of new node as head */
	new_node->next = (*head_ref);

	/* 4. move the head to point to the new node */
	(*head_ref)    = new_node;
}

void pushUser(struct UserNode** head_ref, UserStruct new_data) {
	/* 1. allocate node */
	struct UserNode* new_node = (struct UserNode*) malloc(sizeof(struct UserNode));

	/* 2. put in the data  */
	new_node->data  = new_data;

	/* 3. Make next of new node as head */
	new_node->next = (*head_ref);

	/* 4. move the head to point to the new node */
	(*head_ref)    = new_node;
}

void printPostList(struct PostNode *node) {
	while (node != NULL) {
		printf("user: %s\n", node->data.user);
		printf("post_id: %d\n", node->data.post_id);
		printf("like: %d\n", node->data.like);
		printf("post: %s\n", node->data.post);
		node = node->next;
	}
}

void printUserList(struct UserNode *node) {
	while (node != NULL) {
		printf("%s %s", node->data.user, node->data.password);
		node = node->next;
	}
}


void post(char *p) {
	struct PostStruct post_struct;
	post_struct.post = p;
	printf("\nThe entered string is : %s", p);
}

void printWords(const char *string) {
	// Make a local copy of the string that we can manipulate.
	char * const copy = strdup(string);
	char *space = copy;
	// Find the next space in the string, and replace it with a newline.
	while (space = strchr(space,' ')) *space = '\n';
	// There are no more spaces in the string; print out our modified copy.
	printf("%s\n", copy);
	// Free our local copy
	free(copy);
}

bool prefix(const char *pre, const char *str) {
	return strncmp(pre, str, strlen(pre)) == 0;
}

UserNode* searchUser(struct UserNode* head, UserStruct userStruct) {
	struct UserNode* current = head; // Initialize current
	while (current != NULL) {
		if (strcmp(current->data.user, userStruct.user) == 0)
			return current;
		current = current->next;
	}
	return NULL;
}

PostNode* searchPost(struct PostNode* head, PostStruct postStruct) {
	struct PostNode* current = head; // Initialize current
	while (current != NULL) {
		if (current->data.post_id == postStruct.post_id)
			return current;
		current = current->next;
	}
	return NULL;
}

PostNode* like_post(struct PostNode* head, PostStruct postStruct) {
	struct PostNode* current = head; // Initialize current
	while (current != NULL) {
		if (strcmp(current->data.user, postStruct.user) == 0 && current->data.post_id == postStruct.post_id) {
			current->data.like++;
			return current;
		}
		current = current->next;
	}
	return NULL;
}

bool deletePostNode(struct PostNode** head_ref, PostStruct postStruct) {
	// Store head node
	struct PostNode *temp = *head_ref, *prev;

	// If head node itself holds the key to be deleted
	if (temp != NULL && strcmp(temp->data.user, postStruct.user) == 0  && temp->data.post_id == postStruct.post_id) {
		*head_ref = temp->next; // Changed head
		free(temp); // free old head
		return true;
	}

	// Search for the key to be deleted, keep track of the
	// previous node as we need to change 'prev->next'
	while (temp != NULL && strcmp(temp->data.user, postStruct.user) != 0  && temp->data.post_id != postStruct.post_id) {
		prev = temp;
		temp = temp->next;
	}

	// If key was not present in linked list
	if (temp == NULL)
		return false;

	// Unlink the node from linked list
	prev->next = temp->next;

	free(temp); // Free memory
	return true;
}

void getUserInfo(struct PostNode* head, UserStruct userStruct) {
	struct PostNode* current = head; // Initialize current
	bool userHasAnyPost = false;

	printf("user: %s\n", userStruct.user);
	printf("password: %s\n", userStruct.password);
	printf("\n");
	while (current != NULL) {
		if (strcmp(current->data.user, userStruct.user) == 0 ) {
			userHasAnyPost = true;
			printf("post_id: %d\n", current->data.post_id);
			printf("like: %d\n", current->data.like);
			printf("post: %s\n", current->data.post);
			printf("\n");
		}
		current = current->next;
	}
	if(!userHasAnyPost) {
		printf("user has not any posts!!!\n");
		printf("\n");
	}
}

bool findUser(struct PostNode* head,struct UserNode* user_head, UserStruct userStruct) {
	struct PostNode* current = head; // Initialize current
	struct UserNode* user_current = user_head; // Initialize current
	bool userIsFound = false;
	bool userHasAnyPost = false;

	while (user_current != NULL) {
		if (strcmp(user_current->data.user, userStruct.user) == 0) {
			userIsFound = true;
			printf("user: %s\n", userStruct.user);
			printf("\n");
		}
		user_current = user_current->next;
	}
	if(userIsFound) {
		printf("\n");
		while (current != NULL) {
			if (strcmp(current->data.user, userStruct.user) == 0) {
				userHasAnyPost = true;
				printf("post_id: %d\n", current->data.post_id);
				printf("like: %d\n", current->data.like);
				printf("post: %s\n", current->data.post);
				printf("\n");
			}
			current = current->next;
		}
		if(!userHasAnyPost) {
			printf("user found but has not any posts!!!\n");
			printf("\n");
		}
		return true;
	} else {
		return false;
	}
}

bool isNumeric(const char* s) {
	while(*s) {
		if(*s < '0' || *s > '9')
			return false;
		++s;
	}
	return true;
}

void writeUsersToFile(struct PostNode* head,struct UserNode* user_head) {

	struct PostNode* current = head; // Initialize current
	struct UserNode* user_current = user_head; // Initialize current

	FILE * fptr;
	fptr = fopen("accounts.txt", "w");

	if(fptr==NULL) {
		printf("Error\n");
	} else {
		while (user_current != NULL) {
			int post_count = 0;
			while (current != NULL) {
				if (strcmp(current->data.user, user_current -> data.user) == 0) {
					post_count++;
				}
				current = current->next;
			}
			size_t ln = strlen(user_current->data.password) - 1;
			if (*user_current->data.password && user_current->data.password[ln] == '\n')
				user_current->data.password[ln] = '\0';


			fprintf(fptr, "%s %s %d\n", user_current->data.user,user_current->data.password, post_count);

			printf("\n");
			user_current = user_current->next;
		}
	}

	fclose(fptr);
}

void writePostsToFile(struct PostNode* head) {

	struct PostNode* current = head; // Initialize current

	FILE * fptr;
	fptr = fopen("posts.txt", "w");

	if(fptr==NULL) {
		printf("Error\n");
	} else {
		while (current != NULL) {

			size_t ln = strlen(current->data.post) - 1;
			if (*current->data.post && current->data.post[ln] == '\n')
				current->data.post[ln] = '\0';

			fprintf(fptr, "%s %s %d\n", current->data.post,current->data.user, current->data.like);
			printf("\n");
			current = current->next;
		}

//		size_t ln = strlen(user_current->data.password) - 1;
//		if (*user_current->data.password && user_current->data.password[ln] == '\n')
//			user_current->data.password[ln] = '\0';
	}

	fclose(fptr);
}

void start_program() {
	char *str, c;
	int i = 0, j = 1;

	char signup[]="signup ";
	char login[]="login ";
	char create_post[]="post ";
	char info[]="info";
	char find[]="find_user ";
	char like[]="like ";
	char logout[]="logout";
	char delete_post[]="delete ";
	char write_users[]="write_users";
	char write_posts[]="write_posts";

	// start empty linklist
	struct UserNode* user_head = NULL;
	struct PostNode* post_head = NULL;
	struct UserStruct loggedin_user_struct;
	loggedin_user_struct.user = NULL;
	loggedin_user_struct.password = NULL;

	while(1) {

		str = NULL;
		c = NULL;
		i = 0;
		j = 1;

		str = (char*)malloc(sizeof(char));

		printf("enter your command...\n");

		while (c != '\n') {
			// read the input from keyboard standard input
			c = getc(stdin);

			// re-allocate (resize) memory for character read to be stored
			str = (char*)realloc(str, j * sizeof(char));

			// store read character by making pointer point to c
			str[i] = c;

			i++;
			j++;

		}

		str[i] = '\0'; // at the end append null character to mark end of string


		// signup command
		if(prefix(signup, str)) {

			if(loggedin_user_struct.user == NULL) {
				int init_size = strlen(str);
				char delim[] = " ";
				int k = 0;
				char *array[3];

				char *ptr = strtok(str, delim);

				while(ptr != NULL) {
					if(k < 3) {
						array[k] = ptr;
						k++;
						//printf("%s\n", ptr);
						ptr = strtok(NULL, delim);
					} else {
						break;
					}
				}

				if(k != 3) {
					// user must signup again
					printf("wrong command ,try again, ex: signup username password\n");
					continue;
				}

				struct UserStruct userStruct;
				userStruct.user = array[1];
				userStruct.password = array[2];

				if(searchUser(user_head, userStruct) != NULL) {
					// user must signup again
					printf("username is already taken choose another username!!!\n");
					continue;
				}
				pushUser(&user_head,userStruct);
				//printUserList(user_head);
				printf("you are successfully signed up , please login to continue...\n");
				continue;
			} else {
				printf("another user logged in!!! please logout first and try again...\n");
				continue;
			}
		}

		// login command
		if(prefix(login, str)) {
			int init_size = strlen(str);
			char delim[] = " ";
			int k = 0;
			char *array[3];

			char *ptr = strtok(str, delim);

			while(ptr != NULL) {
				if(k < 3) {
					array[k] = ptr;
					k++;
					//printf("%s\n", ptr);
					ptr = strtok(NULL, delim);
				} else {
					break;
				}
			}

			if(k != 3) {
				// user must signup again
				printf("wrong command ,try again, ex: login [username] [password]\n");
				continue;
			}

			struct UserStruct userStruct;
			userStruct.user = array[1];
			userStruct.password = array[2];

			UserNode* find_user_struct = searchUser(user_head, userStruct);
			if(find_user_struct != NULL && 	(strcmp(find_user_struct->data.password, userStruct.password) == 0)) {
				printf("you are successfully logged in...\n");
				loggedin_user_struct.user = array[1];
				loggedin_user_struct.password = array[2];
			} else {
				printf("wrong username or password!!! ,please try again...\n");
			}
			userStruct.user = NULL;
			userStruct.password = NULL;
			continue;
		}

		// logout command
		if(prefix(logout, str)) {
			if(loggedin_user_struct.user != NULL) {
				if(strlen(str) != 7) {
					printf("wrong command ,try again, ex: info\n");
					continue;
				}
				loggedin_user_struct.user = NULL;
				loggedin_user_struct.password = NULL;
				continue;
			} else {
				printf("you should login first and try again...\n");
				continue;
			}
		}

		// wite command
		if(prefix(write_users, str)) {
			if(loggedin_user_struct.user != NULL) {
				if(strlen(str) != 12) {
					printf("wrong command ,try again, ex: write_users\n");
					continue;
				}
				writeUsersToFile(post_head,user_head);
				continue;
			} else {
				printf("you should login first and try again...\n");
				continue;
			}
		}

		// wite command
		if(prefix(write_posts, str)) {
			if(loggedin_user_struct.user != NULL) {
				if(strlen(str) != 12) {
					printf("wrong command ,try again, ex: write_posts\n");
					continue;
				}
				writePostsToFile(post_head);
				continue;
			} else {
				printf("you should login first and try again...\n");
				continue;
			}
		}

		// create post command
		if(prefix(create_post, str)) {

			if(loggedin_user_struct.user != NULL) {

				struct PostStruct postStruct;
				postStruct.user = loggedin_user_struct.user;
				postStruct.like = 0;
				if(post_head == NULL) {
					postStruct.post_id = 0;
				} else {
					postStruct.post_id = post_head -> data.post_id + 1;
				}

				str += 5;
				postStruct.post = str;

				pushPost(&post_head,postStruct);
				printPostList(post_head);
				printf("post successfuly created...\n");
				continue;
			} else {
				printf("you should login first and try again...\n");
				continue;
			}
		}

		// get user info command
		if(prefix(info, str)) {
			if(loggedin_user_struct.user != NULL) {

				if(strlen(str) != 5) {
					printf("wrong command ,try again, ex: info\n");
					continue;
				}

				getUserInfo(post_head, loggedin_user_struct);
				continue;
			} else {
				printf("you should login first and try again...\n");
				continue;
			}
		}

		// delete post command
		if(prefix(delete_post, str)) {
			if(loggedin_user_struct.user != NULL) {
				int init_size = strlen(str);
				char delim[] = " ";
				int k = 0;
				char *array[2];

				char *ptr = strtok(str, delim);

				while(ptr != NULL) {
					if(k < 2) {
						array[k] = ptr;
						k++;
						//printf("%s\n", ptr);
						ptr = strtok(NULL, delim);
					} else {
						break;
					}
				}

				if(k != 2) {
					printf("wrong command ,please try again, ex: delete [post_id]\n");
					continue;
				}

				struct PostStruct postStruct;

				postStruct.user = loggedin_user_struct.user;
				postStruct.post_id = atoi(array[1]);

				if(deletePostNode(&post_head, postStruct)) {
					printf("post successfully deleted...\n");
				} else {
					printf("wrong post_id, post not found!!! ,please try again...\n");
				}
				postStruct.user = NULL;
				postStruct.post_id = NULL;
				continue;
			} else {
				printf("you should login first and try again...\n");
				continue;
			}
		}

		// find command
		if(prefix(find, str)) {
			if(loggedin_user_struct.user != NULL) {
				int init_size = strlen(str);
				char delim[] = " ";
				int k = 0;
				char *array[2];

				char *ptr = strtok(str, delim);

				while(ptr != NULL) {
					if(k < 2) {
						array[k] = ptr;
						k++;
						//printf("%s\n", ptr);
						ptr = strtok(NULL, delim);
					} else {
						break;
					}
				}

				if(k != 2) {
					printf("wrong command ,try again, ex: find [username]\n");
					continue;
				}

				struct UserStruct userStruct;

				size_t ln = strlen(array[1]) - 1;
				if (*array[1] && array[1][ln] == '\n')
					array[1][ln] = '\0';

				userStruct.user = array[1];

				if(!findUser(post_head,user_head, userStruct)) {
					printf("wrong username , user not found!!! ,please try again...\n");
				}
				userStruct.user = NULL;
				continue;
			} else {
				printf("you should login first and try again...\n");
				continue;
			}
		}

		// like command
		if(prefix(like, str)) {
			if(loggedin_user_struct.user != NULL) {
				int init_size = strlen(str);
				char delim[] = " ";
				int k = 0;
				char *array[3];

				char *ptr = strtok(str, delim);

				while(ptr != NULL) {
					if(k < 3) {
						array[k] = ptr;
						k++;
						//printf("%s\n", ptr);
						ptr = strtok(NULL, delim);
					} else {
						break;
					}
				}

				if(k != 3) {
					printf("wrong command ,try again, ex: like [username] [post_id]\n");
					continue;
				}


				struct PostStruct postStruct;
				postStruct.user = array[1];
				postStruct.post_id = atoi(array[2]);

				PostNode* find_post_node = like_post(post_head, postStruct);
				if(find_post_node == NULL) {
					printf("wrong username or post_id!!! ,please try again...\n");
				} else {
					printf("post successfuly liked...\n");
				}
				postStruct.user = NULL;
				postStruct.post_id = NULL;
				continue;
			} else {
				printf("you should login first and try again...\n");
				continue;
			}
		} else {
			printf("wrong command please try again...\n");
			continue;
		}
	}
}



void get_username_password_from_input() {
	char *str, c;
	int i = 0, j = 1;

	str = (char*)malloc(sizeof(char));

	printf("Enter username and password...ex: username password : ");

	while (c != '\n') {
		// read the input from keyboard standard input
		c = getc(stdin);

		// re-allocate (resize) memory for character read to be stored
		str = (char*)realloc(str, j * sizeof(char));

		// store read character by making pointer point to c
		str[i] = c;

		i++;
		j++;
	}

	str[i] = '\0'; // at the end append null character to mark end of string

	post(str);
	//printf("\nThe entered string is : %s", str);

	//free(str); // important step the pointer declared must be made free
}


int main() {
	start_program();
}