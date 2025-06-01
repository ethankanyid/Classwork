# Homework 1 - Pig Latin

This homework you will write a program to convert words into Pig Latin. Pig Latin
has historical roots going all the way back to to before
[Shakespeare](https://en.wikipedia.org/wiki/Pig_Latin).

## Pig Latin Rules

These rules are straight from [Wikipedia](https://en.wikipedia.org/wiki/Pig_Latin)

- For words that begin with consonant sounds, the initial consonant is moved to
  the end of the word, then "ay" is added.
- When words begin with consonant clusters (multiple consonants that form one 
  sound), the whole sound is moved to the end (before adding "ay") when speaking 
  or writing.
- For words that begin with vowel sounds, one just adds "hay", "way", "nay" or
  "yay" to the end.

## Guidelines

Read every file in this repository. Many of the files will be used across all
three programming homeworks. So gaining an understanding of what each file does
will be important later.

- Don't touch the following files, as they are used to grade your assignment.
    - Testing will be done using `main.c` so do not modify the tests.
    - The build and testing pipeline is defined in `.gitlab-ci.yml` so do not
      modify the pipeline.
- Do the following early and often to complete your assignment successfully.
    - Put your assembly program in `piglatin.s`.
    - Commit and push early and often.
    - Watch the pipeline so you know that you've done it right. (green checkmarks
      good.)
    - Try to ask ChatGPT what's wrong with your program and see what it corrects.
