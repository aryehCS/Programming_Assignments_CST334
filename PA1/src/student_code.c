// Aryeh Freud
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "student_code.h"


/***********
 * Strings *
 ***********/

/**
 * This function takes in a c-string and returns it's length.  It **does not** use the strlen(...) function in string.h
 * @param str The string that we will be finding the length of.  It will be null terminated
 * @return The lenght of the inpurt string
 */
int get_str_length(char* str) {
  // todo - done
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
  // Question: How do we know that we've gotten to the end of a c-string?
  // when we reach the null terminator
  int length = 0;
    while (str[length] != '\0') {
        length++;
    }
  return length;
}

/**
 * Returns a pointer to a copy of the original string.  It **does not** use strcpy or any related function (but may use strlen)
 * @param str An input string that is null terminated
 * @return a new char* that copies the input string str
 */
#define MAX_STR_SIZE 100
char* copy_str(char* str) {
  // todo - done
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
  static char new_str[MAX_STR_SIZE]; // allocate memory for new string
    int i;
    for (i = 0; str[i] != '\0' && i < MAX_STR_SIZE - 1; i++) {
        new_str[i] = str[i];
    } // copies string
    new_str[i] = '\0'; // add null terminator
  return new_str;
}

/**
 * Truncates a string to a the given length, not including the null terminator.  If the given length is longer than the original string the original string is returned unchanged.
 * @param str A null-terminated input string
 * @param new_length The length of the output string.
 */
void truncate_string(char* str, int new_length) {
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
  // todo - done
    int beginning_length = 0;
    while (str[beginning_length] != '\0') {
        beginning_length++;
    } // find length of string
    if (new_length < beginning_length) {
        str[new_length] = '\0'; // truncate string
    }
}

/**
 * Converts a given string, str, to all uppercase letters
 * @param str A null-terminated input string
 */
void to_uppercase(char* str) {
  // todo - done
  for (int i = 0; str[i] != '\0'; i++) { // iterate through string
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32; // convert to uppercase
        }
  }
}

/**
 * Converts a given string, str, to all lowercase letters
 * @param str A null-terminated input string
 */
void to_lowercase(char* str) {
  // todo - done
    for (int i = 0; str[i] != '\0'; i++) { // iterate through string
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32; // convert to lowercase
        }
    }
}

/**
 * Finds the index of the first usage of a target character, starting from 0.  If it doesn't exist return -1
 * @param str A null-terminated input string
 * @param target A character to find in string
 * @return The index of the first usage of the target character in the string
 */
int find_first_index(char* str, char target) {
  // todo - done
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
  for (int i = 0; str[i] != '\0'; i++) { // iterate through string
        if (str[i] == target) {
            return i; // returns index of target char
        }
  }
  return -1;
}

/**
 * Finds the index of the last usage of a target character, starting from 0.  If it doesn't exist return -1
 * @param str A null-terminated input string
 * @param target A character to find in string
 * @return The index of the last usage of the target character in the string
 */
int find_last_index(char* str, char target) {
  // todo
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
  int length = 0;
  while (str[length] != '\0') {
            length++;
  }
  for (int i = length - 1; i >= 0; i--) {
      if (str[i] == target) {
          return i;
      }
  }
        return -1;
}


/**************
 * Structures *
 **************/
/**
 * Create a new person object and return the object
 * @param first_name The first name of the new person as a null-terminated string
 * @param last_name The last name of the new person as a null-terminated string
 * @param age The age of the person as an int
 * @return A Person struct containing the new person
 */
Person person_make_new(char* first_name, char* last_name, int age) {
    // todo - done
    Person new_person;
    int i;

    for (i = 0; first_name[i] != '\0' && i < 50 - 1; i++) {
        new_person.first_name[i] = first_name[i];
    } // copies first name
    new_person.first_name[i] = '\0';

    for (i = 0; last_name[i] != '\0' && i < 50 - 1; i++) {
        new_person.last_name[i] = last_name[i];
    } // copies last name
    new_person.last_name[i] = '\0';

    new_person.age = age; // sets age

    return new_person;
}
/**
 * Return a string containing the full name and age of the person in the format "First Last (age)"
 * @param person The person to get the relevant string for
 * @return A string containing the name of the person
 */
char* person_to_string(Person person) {
  // todo - done
  // hint: sprintf
  static char str[100];
  sprintf(str, "%s %s (%d)", person.first_name, person.last_name, person.age);
  return str; // uses sprintf to format string
}

/**
 * A function to create a new empty group
 * @param group_name A null-terminuated string to name the new group
 * @return A new Group struct
 */
Group group_make_new(char* group_name) {
  // todo - done

    Group new_group;
    new_group.group_name = strdup(group_name); // copies group name
    new_group.num_members = 0; // sets num_members to 0

    for (int i = 0; i < GROUP_MAX_SIZE; i++) {
        new_group.group_members[i] = NULL;
    } // sets group_members to NULL
    return new_group;
}

/**
 * A function to find the total number of people in the group
 * @param group A Group struct that contains some number of people
 * @return The number of users in the group
 */
int num_people_in_group(Group group) {
  // todo - done
  return group.num_members; // returns number of members in group
}
/**
 * Get the number of free spaces remaining in the group
 * @param group A Group struct that contains some number of people
 * @return The number of free spaces in the group
 */
int free_spaces_in_group(Group group) {
  // todo - done
  return GROUP_MAX_SIZE - group.num_members; // returns number of free spaces in group
}

/**
 * Add a person to the group if possible and return the total number of free space in the group. Otherwise return -1.
 * @param group A group struct that contains some number of people
 * @param person_to_add The person to add to the group
 * @return The number of free spaces after add the new person, -1 if the group was already full
 */
int add_person(Group* group, Person* person_to_add) {
  // todo - done
  // Question: Say we have already added a person to the group and try to add them again.  What should be we do?  Where can we check what the expected behavior is?

  if (group -> num_members >= GROUP_MAX_SIZE) {
      return -1; // return -1 if group is full
  }

  for (int i = 0; i < group -> num_members; i++) {
      if (group -> group_members[i] == person_to_add) {
          return -1; // return -1 if person is already in group
      }
  }

  group -> group_members[group -> num_members] = person_to_add;
  group -> num_members++; // adds person to group
  return GROUP_MAX_SIZE - group -> num_members; // # of free spaces in group
}

/**
 * Remove a person from the group if they are in the group, otherwise return -1
 * @param group A Group struct that contains some number of people
 * @param person_to_remove A person to remove from the group
 * @return The number of people remaining in the group, -1 if the person was not in the group
 */
int remove_person(Group* group, Person* person_to_remove) {
  // todo - done

    for (int i = 0; i < group -> num_members; i++) { // iterate through group members
        if (group -> group_members[i] == person_to_remove) { // if person is in group
            for (int j = i; j < group -> num_members - 1; j++) {
                group -> group_members[j] = group -> group_members[j + 1];
            } // shift group members
            group -> group_members[group -> num_members - 1] = NULL;
            group -> num_members--;
            return group -> num_members;
        }
    }
    return -1; // person not found
}



/*
 * Caesar Cipher
 */
/**
 * Shift a character 'left' by the shift amount by subtracting the shift size.
 *  e.g. 'a' with a shift_size = 1 will become 'z'
 * @param input_char
 * @param shift_size
 * @return
 */
char shift_left(char input_char, int shift_size) {
  // todo - done

  if (input_char >= 'A' && input_char <= 'Z') {
      input_char += 32; // convert to lowercase
  }

  if (input_char >= 'a' && input_char <= 'z') {
      input_char = input_char - shift_size;
      if (input_char < 'a') {
          input_char += 26;
      }
  }
  return input_char;
}

/**
 * Shift a character 'right' by the shift amount by subtracting the shift size.
 *  e.g. 'z' with a shift_size = 1 will become 'a'
 * @param input_char
 * @param shift_size
 * @return
 */
char shift_right(char input_char, int shift_size) {
  // todo - done

  if (input_char >= 'A' && input_char <= 'Z') {
      input_char += 32; // convert to lowercase
  }
  if (input_char >= 'a' && input_char <= 'z') {
      input_char = input_char + shift_size;
      if (input_char > 'z') {
          input_char -= 26;
      }
  }
  return input_char;
}

/**
 * Encrypts a string using a given shift.  Note: All characters should be converted to lowercase
 * @param input_str
 * @param shift_size
 * @return
 */
char* encrypt_caesar(char* input_str, int key) {
    // todo - done
    int len = strlen(input_str);
    char* decrypted_str = malloc(len + 1); // allocate memory for decrypted string

    if (!decrypted_str) {
        return NULL; // return NULL if memory allocation fails
    }

    for (int i = 0; i < len; i++) {
        char ch = input_str[i];
        if (ch >= 'A' && ch <= 'Z') {
            ch += 32; // convert to lowercase
        }
        if (ch >= 'a' && ch <= 'z') {
            ch = (ch - 'a' - key + 26) % 26 + 'a'; // decrypt
        }
        decrypted_str[i] = ch; // add to decrypted string
    }
    decrypted_str[len] = '\0';
    return decrypted_str;
}


/**
 * Decrypts a string using a given shift.  Note: All characters should be converted to lowercase
 * @param input_str
 * @param shift_size
 * @return
 */
char* decrypt_caesar(char* input_str, int shift_size) {
  // todo
    int length = strlen(input_str);
    char* encrypted_str = (char*)malloc(length + 1); // allocate memory for encrypted string

    shift_size = shift_size % 26; // make sure shift_size is within 0-25

    for (int i = 0; i < length; i++) { // iterate through string
        if (isalpha(input_str[i])) { // if character is a letter
            char index = islower(input_str[i]) ? 'a' : 'A'; // get index
            encrypted_str[i] = (input_str[i] - index + shift_size) % 26 + index; // encrypt
        } else {
            encrypted_str[i] = input_str[i]; // add to encrypted string
        }
    }

    encrypted_str[length] = '\0';
    return encrypted_str;
}

/*
 * General substitution Cipher
 */

/**
 * Returns true if a given encryption key has a valid decryption key.
 * @param encryption_key
 * @return
 */
bool is_reversible(int* encryption_key) {
  // todo
  return false;
}

/**
 * Generates a decryption key based on the encryption key, if one exists.  Otherwise returns NULL
 * @param encryption_key
 * @return
 */
int* get_decryption_key(int* encryption_key) {
  // todo

  return NULL;
}

/**
 * Takes the input string and the encryption key and encrypts the input string in place
 * @param input_str
 * @param encryption_key
 */
void encrypt_substitution(char* input_str, int* encryption_key) {
  // todo
  return;
}

/**
 * Takes an encrypted input string and a decryption key and decrypts a string in place
 * @param input_str
 * @param decryption_key
 */
void decrypt_substitution(char* input_str, int* decryption_key) {
  // todo
  return;
}
