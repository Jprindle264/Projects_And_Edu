#include <string>
#include <string.h>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <fstream> 


/*Dictionary Trie Project
By Jonathna Prindle
*/

/* Project Goals

1. Implement a trie data structure to incorporate words and definitions.
2. Allow user to enter words and definitions.
3. Give the user the ability to look up definitions.
4. Give the user the ability to print all words and definitions.
5. Create a user interface that allows easy access to all functionality of the program.

Overall, the main goal of this project is to create a basic, alterable, dictionary so that a user
can keep track of various words and definitions while the program is running.
*/

/* Code Structure

Everything is contained in a single file which is called main.cpp. The selected required libraries for
function implementation are included at the very top. The struct for the trie is defined at the top
followed by all the functions utilized within this program. At the main is the main driver function where
a menu for the overall program has been implemented. In the main, required variables are initialized as well
as an initial set of definitions for this program. 


*/


/* Test format

The tests for this project are directed at the user interface and functionality of all components.

Overall Tests:
1. Do all menu selections work?

Independent Tests:
1. Can all words originally initialized with the test be printed using selection 4?
2. Can you add a word and a definition pair?
3. Can you look up if a word is present?
4. Can you look up the definition of a word?
5. After a word/definition has been added, will it print out in addition to all the previous/originally initialized definitions?
6. Can you exit from the menu without error?

After running all independent tests, this should prove the overall test of menu functionality.
*/


using namespace std;

/* Struct for the Trie. Includes a string to hold the definition and a bool that stipulates when each
word ends. The unordered map allows me to store the word and then map to the definition stored within that
word. Values can be user defined which is beneficial to me. Additionally the unordered map container allows
fast look up of values*/

struct Definer{ //This is the overall structure for the Trie
    string definition;
    bool WordEnd;
    unordered_map<char, shared_ptr<Definer>> container;
};



//List of functions for operations.

/* This is a function to create a new node for the trie. Set node equal to a new struct. Word end is initialized to
false. Return the node*/

shared_ptr<Definer> Create_Node(){
    shared_ptr<Definer> node = shared_ptr<Definer> (new Definer);
    node->WordEnd = false;
    return node;
}

/* This is a function to create a new word/definition entry. Constant values required in order not to modify content.
If the root is null, we need to create a new node. A new node is initialized for the root. We then need to iterate
through the acutal word length, adding each char as we go along. All char's get stored for the word, word end changes to
true to indicate the end of the word. Then the definition gets stored with the associated word.

*/


void insert_entry(shared_ptr<Definer> &root, const string &actual_word, const string &definition){
    
    if(root == NULL){
        root = Create_Node();
    }
    
    shared_ptr<Definer> holder = root;
    for(int i = 0; i < actual_word.length(); i++){
        char a = actual_word[i];
        
        //Helps to create a new node if no pre-ecisting path exists.
        if(holder->container.find(a) == holder->container.end()){
            holder->container[a] = Create_Node();
        }
        
        holder = holder->container[a];
    }
    holder->WordEnd = true;
    holder->definition = definition;
}

/*
If root is null, there are no values stored and so the word is empty. Create a holder, intialize with
root value. Iterate through the word's length. If holder is NULL, then the word isn't in the dictionary.
If it is present, return the "Present".
*/

string word_lookup(shared_ptr<Definer> root, string& word){
    if(root == NULL){
        return "Not Present";
    }
    
    shared_ptr<Definer> holder = root;
    for(int i = 0; i < word.length(); i++){ //Specifically this searches through for the word.
        
        holder = holder->container[word[i]];
        if(holder == NULL){
            return "Not Present";
        }
    }
    
    if(holder->WordEnd){
        return "Present";
    }
}


/* Pretty much the same as word lookup. The key difference here is that instead of returning "Present" if
the word is a valid entry, we now return the actual definition for that word. */

string definition_lookup(shared_ptr<Definer> root, string &word){
    
    if (root==NULL){ //if NULL no valid entries are stored.
        return "Not a valid entry";
    }
    
    shared_ptr<Definer> holder = root;
    for(int i = 0; i<word.length(); i++){ //Search for the word.
        holder = holder->container[word[i]];
        if (holder == NULL){
            return "Not a valid entry";
        }
    }
    
    if(holder->WordEnd){ //If word is found, return stored definition.
        return holder->definition;
    }
}

/*
Created an iterator for the unordered map. While it iterates cs.push_back adds the first element, the char, to
the end creating the word. We iterate through the second element to recreate the definition. If we reach end word,
we then pop_back in order to access the other words/definitions. This allows all words and definitions to be printed
out. 
*/

void Print_all(shared_ptr<Definer> current, string cs){
    if(current->WordEnd){
        cout << cs << ": " << current->definition << endl;
    }
    unordered_map<char, shared_ptr<Definer>>:: iterator it;
    for(it = current->container.begin(); it != current->container.end(); it++){
        cs.push_back(it->first);
        Print_all(it->second, cs);
        cs.pop_back();
    }
    
}






int main()
{
    //Initialized variables to be used in the menu.
    shared_ptr<Definer> root = NULL;
    int x;
    bool flag = false;
    
    //Initialized definitions to be used as a starting point for the dictionary.
    insert_entry(root, "laptop", "A computer that is portable and suitable for travel.");
    insert_entry(root, "snow", "Light white flakes floating to the ground.");
    insert_entry(root, "phone", "A telephone");
    insert_entry(root, "cactus", "A succulent plant with thick, fleshy stem that typically bears spikes.");
    insert_entry(root, "car", "A road vehicle.");
    
    
    /*Created a menu in order to access the functions of the dictionary. There are four major functions, the ability
    to add words/definitons, the ability to check if a word is present in the dictionary, the ability to check the
    definition of a particular word, and the ability to print out all words inside the dictionary. There is also an exit
    functon built into the menu. 
    
    
    */
    
    cout <<"Welcome to your personal dictionary. Please select the number of the option you would like to choose.\n";
    cout <<"\n";
    
    do{
    cout <<"Select the number of the option you wish to choose.\n";
    cout <<"1. Add word and definition.\n";
    cout <<"2. Look up if a word is in the dictionary.\n";
    cout <<"3. Look up the definition of a word.\n";
    cout <<"4. Print out all words and definitions.\n";
    cout <<"5. Exit\n";
    cout <<"Selection: ";
    cin >> x;
    cout <<"\n";
    
    if(x == 1){
        string y;
        cout << "Enter Word: ";
        cin >> y;
        string z;
        cout << "Enter Definition:";
        getline(cin >> ws, z); //Took forever to figure out the ws for the spaces in the string.
        insert_entry(root, y, z);
        cout <<"\n";
    }else if (x == 2){
        string b;
        cout <<"Enter a word to check:";
        cin >> b;
        cout <<"\n";
        cout << word_lookup(root, b) << endl;
        cout <<"\n";
    }else if(x==3){
        string a;
        cout<< "Enter a word to look up the definition: ";
        cin >> a;
        cout <<"\n";
        cout <<"Definition: ";
        cout << definition_lookup(root, a) << endl;
        cout <<"\n";
    }
    else if(x==4){
        cout <<"A list of all words and definitions\n";
        cout <<"\n";
        string print_words_def = "";
        Print_all(root, print_words_def);
        cout << "\n";
    }else if (x == 5){
        flag = true;
    }
    else{
        cout <<"Invalid Option, please select a number from the list\n";
        cout <<"\n";
    }
 
    }while(flag != true); 
        
    return 0; 
}

//Future implementation ideas.
/* 
1. Attempted to out put to a text file, which is why fstream is included. Unfortunately ran into an issue where
only one word/definition pair was included. Ran out of time for further implementations.
2. Would also like to implement a definition list from a text file that reads directly into the Trie. This creates
offline functionality.
3. I could have used a switch statement for the menu as opposed to a do while loop. Not sure if it would have been
more efficient. However, I've created many menus with do while loops and this seemed like the most natural implementation
for this project.
4. Potentially implementing a function for printing out the prefixes/affixes of words.

I would also be interested in furthering the functionality of this program. Perhaps creating a basic writing program that could...

5. Incorporate a function for autocompletion, which is what a Trie is typically known for.
6. Incorporate a function as a spell checker while a person is writing to ensure the words stored in the dictionary are properly spelled.

/*
Most of the functions associated with this program run in O(n) time. Trie's typically require a linear search in order to add the words
and definitions, and the same for the insertion/print functionality.
*/

/*Alternative data structures: A single vector of pairs, using just a plain hash map instead of creating a Trie out of a hash map, or perhaps
a ternary search tree. Additionally since almost all the functions run in O(n) time, they are equally slow. 

Ternary search trees would be the most likely. It is a modified version of a trie that used a lot less space, for instance instead of 26 pointers
I would really only need to store three pointers. 
*/