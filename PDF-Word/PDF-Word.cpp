#include <iostream>
#include <fstream>
#include <mupdf/fitz.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

char* extractText(const char* dataPath, const char* inputPath) {

    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, with specifying tessdata path
    if (api->Init(dataPath, "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    Pix* image = pixRead(inputPath);
    api->SetImage(image);
    
    // Get OCR result

    printf("\nConverting...");
    char* extractedText = api->GetUTF8Text();
    printf("\nText Output:\n\n%s", extractedText);

    // Destroy used object and release memory
    api->End();
    delete api;
    pixDestroy(&image);

    return extractedText;
}



void createWordDocument(const std::string& outputFilePath, const std::string& extractedText) {

    std::ofstream outputFile(outputFilePath);
    if (outputFile.is_open()) {
        outputFile << extractedText;
        outputFile.close();
        std::cout << "Conversion successful. Output saved to: " << outputFilePath << std::endl;
    }
    else {
        std::cerr << "Failed to create the output Word file." << std::endl;
        return;
    }

}


int main()
{
    // Set the data path to the tessdata directory containing language data files
    const char* dataPath = "C:/Users/Tarun/Desktop/Code/pdftoword/tessdata";

    // Set the ouput file
    std::string outputFilePath = "C:/Users/Tarun/Desktop/PdttoText/output2.docx";

    const char* inputPath = "C:/Users/Tarun/Desktop/PdttoText/pdf1.png";
    printf("Initialised\n");
    char* extractedText = extractText(dataPath, inputPath);

    // Creates a word document
    createWordDocument(outputFilePath, extractedText);

    return 0;
}
