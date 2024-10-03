#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void compressFile(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);
    
    if (!inFile) {
        cerr << "Error opening input file!" << endl;
        return;
    }
    if (!outFile) {
        cerr << "Error opening output file!" << endl;
        return;
    }

    char currentChar, previousChar;
    int count = 0;
    
    inFile.get(previousChar);
    count = 1;

    while (inFile.get(currentChar)) {
        if (currentChar == previousChar && count < 255) {
            count++;
        } else {
            outFile.put(previousChar);
            outFile.put(count);
            previousChar = currentChar;
            count = 1;
        }
    }

    outFile.put(previousChar);
    outFile.put(count);

    inFile.close();
    outFile.close();
    
    cout << "File compressed successfully!" << endl;
}

void decompressFile(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);

    if (!inFile) {
        cerr << "Error opening input file!" << endl;
        return;
    }
    if (!outFile) {
        cerr << "Error opening output file!" << endl;
        return;
    }

    char character;
    unsigned char count;

    while (inFile.get(character) && inFile.get(reinterpret_cast<char&>(count))) {
        for (int i = 0; i < count; i++) {
            outFile.put(character);
        }
    }

    inFile.close();
    outFile.close();
    
    cout << "File decompressed successfully!" << endl;
}

int main() {
    string inputFile, outputFile;
    int choice;

    cout << "File Compression and Decompression Tool\n";
    cout << "1. Compress a file\n";
    cout << "2. Decompress a file\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter the name of the file to compress: ";
        cin >> inputFile;
        cout << "Enter the name of the output compressed file: ";
        cin >> outputFile;
        compressFile(inputFile, outputFile);
    } else if (choice == 2) {
        cout << "Enter the name of the file to decompress: ";
        cin >> inputFile;
        cout << "Enter the name of the output decompressed file: ";
        cin >> outputFile;
        decompressFile(inputFile, outputFile);
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
