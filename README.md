Assignment components

Strings

(25 points)

Remember from class that Strings in C are null-terminated character arrays. In this section you should practice using string functions and mimic them on your own. Note that some of these functions (e.g. copy_str and length_of_str) are available in the c string library, but you should implement your own version of them. I will reiterate this in the code itself, and use of these standard functions will result in a 0 for these problems.

Specific todos and point values

int get_str_length(char* str);                      // 5 points
char* copy_str(char* str);                          // 5 points
void truncate_string(char* str, int new_length);    // 4 points
void to_uppercase(char* str);                       // 4 points
void to_lowercase(char* str);                       // 4 points
void find_first_index(char* str, char target);      // 2 points
void find_last_index(char* str, char target);       // 1 points
Structs

(25 points)

Structs in C are contiguous memory objects, where we group together more primative object types to make more complex types. They are similar to objects in object-oriented languages, but consist of only the data instead of the associated functions as well. With that said, we can also have functions associated with them, albeit with a more verbose usage (i.e. a longer and more explicit set of input parameters). In this section we'll practice both designing new structs, but also see how to use them and how to make functions for them.

Specific todos and point values

struct Group;                                                       // 5 points
Person person_make_new(char* first_name, char* last_name, int age); // 4 points
char* person_to_string(Person person);                              // 2 points
Group group_make_new(char* group_name);                             // 3 points
int num_people_in_group(Group* group);                              // 2 points
int free_spaces_in_group(Group* group);                             // 4 points
int add_person(Group* group, Person* person_to_add);                // 4 points
int remove_person(Group* group, Person* person_to_remove);          // 1 point
NOTE: You will need to change the struct Group definition in student_code.h to pass the unit tests. The void* types are placeholders for you to change in the struct in order to get unit tests to pass.

Caesar Cipher

(30 points)

C is ideal for low-level bit manipulation, making it perfect for playing around with encryption. We're going to be doing this through the Caesar cipher, which is one of the earliest known encryption ciphers. The core idea of a caesar cipher is that you "shift" the letter of the input by some amount. For instance, a caesar cipher with shift of 1 would change 'a' to 'b' and 'z' to 'a'.

Your job is to implement these functions!

char shift_left(char input_char, int shift_size);     // 10 points
char shift_right(char input_char, int shift_size);    // 10 points
void encrypt_caesar(char* input_str, int shift_size); // 5 points
void decrypt_caesar(char* input_str, int shift_size); // 5 points
General substitution cipher (bonus points)

(10 bonus points)

This general substituion cipher will take in a list of shifts and make the appropriate replacements. Since it is extra credit details are left to you to figure out, but some unit tests are provided.

bool is_reversible(int[] encryption_key);                             // 4 points
int* get_decryption_key(int[] encryption_key);                        // 4 points
void encrypt_substitution(char* input_str, int[] encryption_key);     // 1 point
void decrypt_substitution(char* input_str, int[] get_decryption_key); // 1 point
