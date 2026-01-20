# Experience coding with LLM

The development was purposely made iteratively, since the AI likes to rush things and be imprecise when giving long or difficult prompts.

The initial prompt was the whole assignment text, but it was also clearly stating to not do anything and wait for more instructions on how to proceed. Therefore the AI was instructed to generate well structured code, with doxygen documentation, short functions, following all C standards, compiled with the most restrictive flags without any errors, meaningful variable and function names, unit testing with unity, Makefile and files divided in the correct directories, and frequent, meaningful commits.
The output showed the AI's understanding of the constraints.

The first real task was to create the API, which it did successfully without any mistakes, followed by the actual functions one by one.

The first problems came up with the put function for which I needed to tell it to check if the table should be resized, and to make a helper function for it.

Next it started being inconsistent, adding documentation that was already present in the header to the source file, while also using wrong function names.

It then changed int hash_table_contains_key to bool hash_table_contains_key, again an inconsistency with the header file.
In hash_table_remove it forgot to use generic void* pointers and a user given compare function and started using char pointers and strcmp, while also returning 0 instead of -1 on failure.

At the end in the free function it tried to free the key and the values, going against what it wrote in the header file once again and also going against the proposed implementation of put.

Two last small issues were inconsistencies in using const, also trying to modify const values and adding comments in Italian instead of English as instructed.

## Main Issues encountered

Summarizing, the AI is really fast at writing down code but it's not always perfect, the main problems were:

 **Respecting function signatures**

 **Memory management**

 **Consistency** especially across different files, and sometimes across different functions of the same one.