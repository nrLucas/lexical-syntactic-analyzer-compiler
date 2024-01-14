# Lexical and Syntactic Analyzer in C++

This repository contains a comprehensive Lexical and Syntactic Analyzer implemented in C++ for programming language processing. The code is structured to efficiently tokenize and parse source code, adhering to specified grammar rules.

## Features
- **Lexical Analysis**: The code includes an extensive lexical analyzer (`scanner` function) that breaks down the input source code into tokens. These tokens are identified based on various categories like identifiers, literals, operators, and reserved words.
- **Syntactic Analysis**: Utilizing a series of grammar rules and state transitions defined in accompanying CSV files (`slr_action.csv` and `slr_desvio.csv`), the analyzer performs syntactic analysis. It checks the structure of the token sequence against the defined grammar.
- **Error Handling**: Both lexical and syntactic errors are identified and reported, offering insights into the specific location (line and column) of the error within the source code.

## Components
1. **Main Analyzer Code**: The core functionality is encapsulated in the provided C++ file.
2. **SLR Transition Tables**: Two CSV files representing the SLR (Simple LR Parsing) transitions used in the syntactic analysis phase.

## Usage
- Compile the C++ code in a standard C++ environment.
- The SLR transition tables should be in the same directory as the executable for the analyzer to function correctly.
- Input your source code to be analyzed, and the program will output the tokens, syntactic structure, and any errors encountered.
