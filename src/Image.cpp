#include <iostream>
#include <vector>
#include <string>
#include "Image.h"

using namespace std;

int testPassRate = 0;

Header ReadHeader(string file, Header headerObj){ //string is passed in.;
    ifstream inFile;
    inFile.open(file, ios_base :: binary); //Open the passed in file.

    if(inFile.is_open()){
        //cout << "Header has been opened successfully. Running ReadHeader" << endl;
    }
    else{
        //cout << "Header has not been opened. Debug ReadHeader" << endl;
    }
    inFile.read((char*)&headerObj.idLength,sizeof(headerObj.idLength));
    inFile.read((char*)&headerObj.colorMapType, sizeof(headerObj.colorMapType));
    inFile.read((char*)&headerObj.dataTypeCode, sizeof(headerObj.dataTypeCode));
    inFile.read((char*)&headerObj.colorMapOrigin, sizeof(headerObj.colorMapOrigin));
    inFile.read((char*)&headerObj.colorMapLength, sizeof(headerObj.colorMapLength));
    inFile.read((char*)&headerObj.colorMapDepth, sizeof(headerObj.colorMapDepth));
    inFile.read((char*)&headerObj.xOrigin, sizeof(headerObj.xOrigin));
    inFile.read((char*)&headerObj.yOrigin, sizeof(headerObj.yOrigin));
    inFile.read((char*)&headerObj.width, sizeof(headerObj.width));
    inFile.read((char*)&headerObj.height, sizeof(headerObj.height));
    inFile.read((char*)&headerObj.bitsPerPixel, sizeof(headerObj.bitsPerPixel));
    inFile.read((char*)&headerObj.imageDescriptor, sizeof(headerObj.imageDescriptor)); //End of Header Reading

    /* cout << "***TEST CODE***" << endl;
    cout << "ID Length: " << (int)headerObj.idLength << endl; //Test code. Comment out later.
    cout << "Color Map Type: " << (int)headerObj.colorMapType << endl;
    cout << "Data Type Code: " << (int)headerObj.dataTypeCode << endl;
    cout << "Color Map Origin: " << headerObj.colorMapOrigin << endl;
    cout << "Color Map Length: " << headerObj.colorMapLength << endl;
    cout << "Color Map Depth: " << (int)headerObj.colorMapDepth << endl;
    cout << "X Origin: " << headerObj.xOrigin << endl;
    cout << "Y Origin: " << headerObj.yOrigin << endl;
    cout << "Width: " << headerObj.width << endl;
    cout << "Height: " << headerObj.height << endl;
    cout << "Bits Per Pixel: " << (int)headerObj.bitsPerPixel << endl;
    cout << "Image Descriptor: " << (int)headerObj.imageDescriptor << endl;

    cout << "Header data has been successfully read. Closing File." << endl; */

    inFile.close();
    if(inFile.is_open()){
        //cout << "File is still open. ReadHeader has not ended." << endl;
    }
    else{
        //cout << "File has successfully closed. ReadHeader has ended." << endl;
    }
    return headerObj;
}

vector<Pixel*> ReadPixelData(Header& headerObj, string file, vector<Pixel*> pixelData){
    //We need to read the pixel data provided by the image. All pixel data needs to be placed into the vector.
    ifstream inFile(file, ios_base :: binary);
    Pixel pixelObj;

    if(inFile.is_open()) {
        //cout << "File has opened successfully. Running ReadPixelData" << endl;
    }
    else{
        //cout << "File has not been opened. Debug ReadPixelData";
    }

    char headerData[18]; //18 bytes, reads through header data since it isn't needed.
    inFile.read(headerData,sizeof(headerData));
    int size = (headerObj.height*headerObj.width);

    for(int i = 0; i < size; i++) {
        Pixel* temp = new Pixel;

        inFile.read((char*)&temp->blue, 1);
        inFile.read((char*)&temp->green, 1);
        inFile.read((char*)&temp->red, 1);

        pixelData.push_back(temp);
    }

    inFile.close();

    if(inFile.is_open()) {
        //cout << "File is still open." << endl;
    }
    else{
        //cout << "File has closed. ReadPixelData complete." << endl;
    }
    return pixelData;
}

void WriteFile(Header& headerObj, vector<Pixel*> &pixelData, string file){ //Creates a new file and writes the information given to it. Needs to be worked on
    ofstream outFile;
    outFile.open(file, ios_base :: binary);

    if(outFile.is_open()) {
        //cout << "File has been opened. Running WriteFile." << endl;
    }
    else{
        //cout << "File has not been opened. Debug WriteFile" << endl;
    }

    outFile.write((char*)&headerObj.idLength,sizeof(headerObj.idLength));
    outFile.write((char*)&headerObj.colorMapType, sizeof(headerObj.colorMapType));
    outFile.write((char*)&headerObj.dataTypeCode, sizeof(headerObj.dataTypeCode));
    outFile.write((char*)&headerObj.colorMapOrigin, sizeof(headerObj.colorMapOrigin));
    outFile.write((char*)&headerObj.colorMapLength, sizeof(headerObj.colorMapLength));
    outFile.write((char*)&headerObj.colorMapDepth, sizeof(headerObj.colorMapDepth));
    outFile.write((char*)&headerObj.xOrigin, sizeof(headerObj.xOrigin));
    outFile.write((char*)&headerObj.yOrigin, sizeof(headerObj.yOrigin));
    outFile.write((char*)&headerObj.width, sizeof(headerObj.width));
    outFile.write((char*)&headerObj.height, sizeof(headerObj.height));
    outFile.write((char*)&headerObj.bitsPerPixel, sizeof(headerObj.bitsPerPixel));
    outFile.write((char*)&headerObj.imageDescriptor, sizeof(headerObj.imageDescriptor)); //End of Header Writing

    int size = (headerObj.width * headerObj.height); //Size of pixelData vector passed in.

    /*cout << "***TEST CODE***" << endl;
    cout << "ID Length: " << (int)headerObj.idLength << endl; //Test code. Comment out later.
    cout << "Color Map Type: " << (int)headerObj.colorMapType << endl;
    cout << "Data Type Code: " << (int)headerObj.dataTypeCode << endl;
    cout << "Color Map Origin: " << headerObj.colorMapOrigin << endl;
    cout << "Color Map Length: " << headerObj.colorMapLength << endl;
    cout << "Color Map Depth: " << (int)headerObj.colorMapDepth << endl;
    cout << "X Origin: " << headerObj.xOrigin << endl;
    cout << "Y Origin: " << headerObj.yOrigin << endl;
    cout << "Width: " << headerObj.width << endl;
    cout << "Height: " << headerObj.height << endl;
    cout << "Bits Per Pixel: " << (int)headerObj.bitsPerPixel << endl;
    cout << "Image Descriptor: " << (int)headerObj.imageDescriptor << endl; */

    //cout << "File has been written to header" << endl;

    for(unsigned int i = 0; i < size; i++){ //int was -1, needs the values from the VECTOR.
        outFile.write((char*)&pixelData.at(i)->blue, 1); //Blue
        outFile.write((char*)&pixelData.at(i)->green, 1); //Green
        outFile.write((char*)&pixelData.at(i)->red, 1); //Red
    }

    outFile.close();
    if(outFile.is_open()) {
        //cout << "File is still open." << endl;
    }
    else{
        //cout << "File has been closed. End of WriteFile." << endl;
    }
}

vector <Pixel*> Multiply(vector <Pixel*>& pixelDataOne, vector <Pixel*>& pixelDataTwo){
    vector<Pixel*> finalData; //Data used to store the newly created pixel data
    float blueOne, blueTwo;
    float greenOne, greenTwo;
    float redOne, redTwo;

    for(int i = 0; i < pixelDataOne.size(); i++) { //Iterates through the 'first layer' that being pixelDataOne
        Pixel* temp = new Pixel;

        blueOne = pixelDataOne.at(i)->blue; //Initializes each value within each vector. Preps for the blend
        blueTwo = pixelDataTwo.at(i)->blue;

        greenOne = pixelDataOne.at(i)->green;
        greenTwo = pixelDataTwo.at(i)->green;

        redOne = pixelDataOne.at(i)->red;
        redTwo = pixelDataTwo.at(i)->red;

        //Actual start of blend. We just need to multiply the two values together and keep it in an acceptable range.
        temp->blue = ((blueOne * blueTwo) / (float)255) + .5f; //Almost positive the error is in this block due to swap from unsigned char to float. Needs to be within 255.
        temp->green = ((greenOne * greenTwo) / (float)255) + .5f;
        temp->red = ((redOne * redTwo) / (float)255) + .5f; //Is the data larger than the original amount of pixeDataOne size?

        finalData.push_back(temp);
    }
    return finalData;
}

vector <Pixel*> Subtract(vector <Pixel*>& pixelDataOne, vector <Pixel*>& pixelDataTwo){
    vector<Pixel*> finalData; //Data used to store the newly created pixel data
    for(unsigned int i = 0; i < pixelDataOne.size(); i++){
        Pixel* temp = new Pixel;
        int B,G,R;

        B = ((((pixelDataOne.at(i)->blue)) - ((pixelDataTwo.at(i)->blue))));
        G = ((((pixelDataOne.at(i)->green)) - ((pixelDataTwo.at(i)->green))));
        R = ((((pixelDataOne.at(i)->red)) - ((pixelDataTwo.at(i)->red))));

        //EDGE CASES: If the pixel values are less than zero, set then to zero to avoid discrepencies.
        if (B < 0){
            B = 0;
        }

        if(G < 0){
            G = 0;
        }

        if(R < 0){
            R = 0;
        }

        temp->blue = B;
        temp->green = G;
        temp->red = R;

        finalData.push_back(temp);
    }
    return finalData;
}

vector <Pixel*> Screen(vector <Pixel*>& pixelDataOne, vector <Pixel*>& pixelDataTwo){
    vector <Pixel*> finalData;
    float R, R2;
    float G, G2;
    float B, B2;

    for(int i = 0; i < pixelDataOne.size(); i++){
        Pixel* temp = new Pixel;

        B = pixelDataOne.at(i)->blue; //Initialize all of the variables
        B2 = pixelDataTwo.at(i)->blue;
        G = pixelDataOne.at(i)->green;
        G2 = pixelDataTwo.at(i)->green;
        R = pixelDataOne.at(i)->red;
        R2 = pixelDataTwo.at(i)->red;

        temp->red = ((1-((float)1-(R/(float)255))*((float)1-(R2/(float)255)))*255)+.5f; //Implementation of the algorithm
        temp->green = ((1-((float)1-(G/(float)255))*((float)1-(G2/(float)255)))*255)+.5f;
        temp->blue = ((1-((float)1-(B/(float)255))*((float)1-(B2/(float)255)))*255)+.5f;

        finalData.push_back(temp);
    }
    return finalData;
}

vector <Pixel*> Overlay(vector <Pixel*>& pixelDataOne, vector <Pixel*>& pixelDataTwo) {
    vector<Pixel *> finalData;
    float finalRed, finalGreen, finalBlue;

    for (int i = 0; i < pixelDataOne.size(); i++) {
        Pixel *temp = new Pixel;

        float R = (float) pixelDataOne.at(i)->red / (float) 255;
        float G = (float) pixelDataOne.at(i)->green / (float) 255;
        float B = (float) pixelDataOne.at(i)->blue / (float) 255;

        float R2 = (float) pixelDataTwo.at(i)->red / (float) 255;
        float G2 = (float) pixelDataTwo.at(i)->green / (float) 255;
        float B2 = (float) pixelDataTwo.at(i)->blue / (float) 255;

        //EDGE CASES: If the values passed are less than the rounding value, create a separate result
        if (R2 <= .5) {
            finalRed = ((2 * R * R2) * 255) + .5f;
        }
        //Else continue with the current algorithm.
        else {
            finalRed = ((1.0f - (2.0f * (1.0f - R) * (1.0f - R2))) * 255) + .5f;
        }
        if (G2 <= .5) {
            finalGreen = ((2 * G * G2) * 255) + .5f;
        } else {
            finalGreen = ((1.0f - (2.0f * (1.0f - G) * (1.0f - G2))) * 255) + .5f;
        }
        if (B2 <= .5) {
            finalBlue = ((2 * B * B2) * 255) + .5f;
        } else {
            finalBlue = ((1.0f - (2.0f * (1.0f - B) * (1.0f - B2))) * 255) + .5f;
        }

        temp->red = finalRed;
        temp->green = finalGreen;
        temp->blue = finalBlue;

        finalData.push_back(temp);
    }
    return finalData;
}

vector <Pixel*> addGreen(vector <Pixel*>& pixelData){
    vector <Pixel*> finalData;

    for(int i = 0; i < pixelData.size(); i++){ //This whole method was pretty straightforward
        Pixel* temp = new Pixel;
        int g200 = ((pixelData.at(i)->green)+200);

        if(g200 > 255){
            g200 = 255;
        }

        temp->red = pixelData.at(i)->red;
        temp->green = g200;
        temp->blue = pixelData.at(i)->blue;

        finalData.push_back(temp);
    }
    return finalData;
}

vector<Pixel*> SeparateRed(vector <Pixel*>& pixelDataOne) {
    vector <Pixel*> RedData;
    for (unsigned int i = 0; i < pixelDataOne.size(); i++) {
        Pixel* tempRed = new Pixel;

        tempRed->red = pixelDataOne.at(i)->red; //Extract all of the red values from the dataset passed in
        tempRed->green = pixelDataOne.at(i)->red;
        tempRed->blue = pixelDataOne.at(i)->red;
        RedData.push_back(tempRed);
    }
    return RedData; //return it
}

vector<Pixel*> SeparateGreen(vector <Pixel*>& pixelDataOne) { //Do exactly what is above, but for Green
    vector <Pixel*> GreenData;

    for (unsigned int i = 0; i < pixelDataOne.size(); i++){
        Pixel* tempGreen = new Pixel;

        tempGreen->red = pixelDataOne.at(i)->green;
        tempGreen->green = pixelDataOne.at(i)->green;
        tempGreen->blue = pixelDataOne.at(i)->green;
        GreenData.push_back(tempGreen);
    }
    return GreenData;
}

vector<Pixel*> SeparateBlue(vector <Pixel*>& pixelDataOne) {//Do exactly what is above, but for Blue
    vector<Pixel*> BlueData;

    for (unsigned int i = 0; i < pixelDataOne.size(); i++) {
        Pixel *tempBlue = new Pixel;

        tempBlue->red = pixelDataOne.at(i)->blue;
        tempBlue->green = pixelDataOne.at(i)->blue;
        tempBlue->blue = pixelDataOne.at(i)->blue;
        BlueData.push_back(tempBlue);
    }
    return BlueData;
}

vector<Pixel*> Combine(vector <Pixel*>& fileDataRed, vector <Pixel*>& fileDataGreen, vector <Pixel*> fileDataBlue) {
    vector<Pixel *> combineVector;

    for (int i = 0; i < fileDataRed.size(); i++) {
        Pixel *temp = new Pixel;

        temp->red = fileDataBlue.at(i)->blue; //Takes all of the passed in PixelData and mashes it together under temp
        temp->green = fileDataGreen.at(i)->green;
        temp->blue = fileDataRed.at(i)->red;

        combineVector.push_back(temp); //Pushes data for each pixel onto CombineVector and returns it.
    }
    return combineVector;
}

vector <Pixel*> Rotate(vector <Pixel*>& fileData){
    vector <Pixel*> finalData;

    for(int i = 1; i <= fileData.size(); i++){
        Pixel* temp = new Pixel;
        
        temp->red = (fileData.at(fileData.size()-i)->red);
        temp->green = (fileData.at(fileData.size()-i)->green);
        temp->blue = (fileData.at(fileData.size()-i)->blue);

        finalData.push_back(temp);
    }
    return finalData;
}
vector<Pixel*> ScaleRed(vector <Pixel*>& fileData){ //Scales red to
    vector<Pixel*> finalData;

    for(int i = 0; i < fileData.size(); i++){
        Pixel* temp = new Pixel;
        int red;

        red = 4*fileData.at(i)->red;
        temp->green = fileData.at(i)->green;
        temp->blue = (0*((((int)fileData.at(i)->blue))));

        //EDGE Case. Red is over 255 from the multiply.
        if(red > 255){
            temp->red = 255;
        }
        else{
            temp->red = red;
        }
        finalData.push_back(temp);
    }
    return finalData;
}

void TestOne() {
    cout << "Test #1...... ";

    Header layer1Header;
    layer1Header = ReadHeader("input/layer1.tga", layer1Header);

    vector<Pixel*> layer1Data;
    layer1Data = ReadPixelData(layer1Header, "input/layer1.tga", layer1Data);

    Header pattern1Header;
    pattern1Header = ReadHeader("input/pattern1.tga", pattern1Header);

    vector<Pixel*> pattern1Data;
    pattern1Data = ReadPixelData(pattern1Header, "input/pattern1.tga",pattern1Data);

    vector<Pixel*> finalData;
    finalData = Multiply(layer1Data, pattern1Data);

    WriteFile(layer1Header, finalData, "output/part1.tga");

    Header comparisonHeader;
    comparisonHeader = ReadHeader("examples/EXAMPLE_part1.tga", comparisonHeader);
    vector<Pixel*> comparisonData;
    comparisonData = ReadPixelData(comparisonHeader,"examples/EXAMPLE_part1.tga",comparisonData);

    if(comparisonData == finalData){ //If the entirety of the test compiles without issue, the test has passed. Else it has Failed.
        cout << "Passed!" << endl;
        testPassRate++;
    }
    else{
        cout << "Failed!" << endl;
    }
}

void TestTwo() {
    cout << "Test #2...... ";

    Header layer2Header;
    layer2Header = ReadHeader("input/layer2.tga", layer2Header);

    vector<Pixel*> layer2Data;
    layer2Data = ReadPixelData(layer2Header, "input/layer2.tga", layer2Data);

    Header carHeader;
    carHeader = ReadHeader("input/car.tga", carHeader);

    vector<Pixel*> carData;
    carData = ReadPixelData(carHeader, "input/car.tga",carData);

    vector<Pixel*> finalData;
    finalData = Subtract(carData,layer2Data);

    WriteFile(layer2Header, finalData, "output/part2.tga");

    Header comparisonHeader;
    comparisonHeader = ReadHeader("examples/EXAMPLE_part2.tga", comparisonHeader);
    vector<Pixel*> comparisonData;
    comparisonData = ReadPixelData(comparisonHeader,"examples/EXAMPLE_part2.tga",comparisonData);

    if(comparisonData == finalData){
        cout << "Passed!" << endl;
        testPassRate++;
    }
    else{
        cout << "Failed!" << endl;
    }
}

void TestThree() {
    cout << "Test #3...... ";

    Header layer1Header;
    layer1Header = ReadHeader("input/layer1.tga", layer1Header);

    vector<Pixel*> layer1Data;
    layer1Data = ReadPixelData(layer1Header, "input/layer1.tga", layer1Data);

    Header pattern2Header;
    pattern2Header = ReadHeader("input/pattern2.tga", pattern2Header);

    vector<Pixel*> pattern2Data;
    pattern2Data = ReadPixelData(pattern2Header, "input/pattern2.tga",pattern2Data);

    vector<Pixel*> MultiplyData;
    MultiplyData = Multiply(layer1Data, pattern2Data);

    Header textHeader;
    textHeader = ReadHeader("input/text.tga", textHeader);

    vector<Pixel*> textData;
    textData = ReadPixelData(textHeader, "input/text.tga", textData);

    vector<Pixel*> finalData;
    finalData = Screen(MultiplyData, textData);

    WriteFile(layer1Header, finalData, "output/part3.tga");

    Header comparisonHeader;
    comparisonHeader = ReadHeader("examples/EXAMPLE_part3.tga", comparisonHeader);
    vector<Pixel*> comparisonData;
    comparisonData = ReadPixelData(comparisonHeader,"examples/EXAMPLE_part3.tga",comparisonData);

    if(comparisonData == finalData){
        cout << "Passed!" << endl;
        testPassRate++;
    }
    else{
        cout << "Failed!" << endl;
    }
}
void TestFour() {
    cout << "Test #4...... ";

    Header layer2Header;
    layer2Header = ReadHeader("input/layer2.tga", layer2Header);

    vector<Pixel *> layer2Data;
    layer2Data = ReadPixelData(layer2Header, "input/layer2.tga", layer2Data);

    Header circlesHeader;
    circlesHeader = ReadHeader("input/circles.tga", circlesHeader);

    vector<Pixel *> circlesData;
    circlesData = ReadPixelData(circlesHeader, "input/circles.tga", circlesData);

    vector<Pixel*> MultiplyData;
    MultiplyData = Multiply(layer2Data, circlesData);

    Header pattern2Header;
    pattern2Header = ReadHeader("input/pattern2.tga", pattern2Header);

    vector<Pixel*> pattern2Data;
    pattern2Data = ReadPixelData(pattern2Header, "input/pattern2.tga", pattern2Data);

    vector<Pixel*> finalData;
    finalData = Subtract(MultiplyData,pattern2Data);

    WriteFile(layer2Header, finalData, "output/part4.tga");

    Header comparisonHeader;
    comparisonHeader = ReadHeader("examples/EXAMPLE_part4.tga", comparisonHeader);
    vector<Pixel*> comparisonData;
    comparisonData = ReadPixelData(comparisonHeader,"examples/EXAMPLE_part4.tga",comparisonData);

    if(comparisonData == finalData){
        cout << "Passed!" << endl;
        testPassRate++;
    }
    else{
        cout << "Failed!" << endl;
    }
}

void TestFive() {
    cout << "Test #5...... ";

    Header layer1Header;
    layer1Header = ReadHeader("input/layer1.tga", layer1Header);

    vector<Pixel*> layer1Data;
    layer1Data = ReadPixelData(layer1Header, "input/layer1.tga", layer1Data);

    Header pattern1Header;
    pattern1Header = ReadHeader("input/pattern1.tga", pattern1Header);

    vector<Pixel*> pattern1Data;
    pattern1Data = ReadPixelData(pattern1Header, "input/pattern1.tga", pattern1Data);

    vector<Pixel*> finalData;
    finalData = Overlay(layer1Data, pattern1Data);

    WriteFile(layer1Header, finalData, "output/part5.tga");

    Header comparisonHeader;
    comparisonHeader = ReadHeader("examples/EXAMPLE_part5.tga", comparisonHeader);
    vector<Pixel*> comparisonData;
    comparisonData = ReadPixelData(comparisonHeader,"examples/EXAMPLE_part5.tga",comparisonData);

    if(comparisonData == finalData){
        cout << "Passed!" << endl;
        testPassRate++;
    }
    else{
        cout << "Failed!" << endl;
    }
}

void TestSix() {
    cout << "Test #6...... ";

    Header carHeader;
    carHeader = ReadHeader("input/car.tga", carHeader);

    vector<Pixel*> carData;
    carData = ReadPixelData(carHeader, "input/car.tga", carData);

    vector <Pixel*> finalData;
    finalData = addGreen(carData);

    WriteFile(carHeader, finalData, "output/part6.tga");

    Header comparisonHeader;
    comparisonHeader = ReadHeader("examples/EXAMPLE_part6.tga", comparisonHeader);
    vector<Pixel*> comparisonData;
    comparisonData = ReadPixelData(comparisonHeader,"examples/EXAMPLE_part6.tga",comparisonData);

    if(comparisonData == finalData){
        cout << "Passed!" << endl;
        testPassRate++;
    }
    else{
        cout << "Failed!" << endl;
    }
}
void TestSeven() {
    cout << "Test #7...... ";

    Header carHeader;
    carHeader = ReadHeader("input/car.tga", carHeader);

    vector<Pixel*> carData;
    carData = ReadPixelData(carHeader, "input/car.tga",carData);

    vector<Pixel*> finalData;
    finalData = ScaleRed(carData);

    WriteFile(carHeader, finalData, "output/part7.tga");

    Header comparisonHeader;
    comparisonHeader = ReadHeader("examples/EXAMPLE_part7.tga", comparisonHeader);
    vector<Pixel*> comparisonData;
    comparisonData = ReadPixelData(comparisonHeader,"examples/EXAMPLE_part7.tga",comparisonData);

    if(comparisonData == finalData){
        cout << "Passed!" << endl;
        testPassRate++;
    }
    else{
        cout << "Failed!" << endl;
    }
}

void TestEight() {
    cout << "Test #8...... " << endl;

    Header carHeader;
    carHeader = ReadHeader("input/car.tga", carHeader);

    vector<Pixel*> carData;
    carData = ReadPixelData(carHeader, "input/car.tga", carData);

    vector<Pixel*> RedData;
    RedData = SeparateRed(carData);
    WriteFile(carHeader,RedData,"output/part8_r.tga");

    vector<Pixel*> GreenData;
    GreenData = SeparateGreen(carData);
    WriteFile(carHeader, GreenData, "output/part8_g.tga");

    vector<Pixel*> BlueData;
    BlueData = SeparateBlue(carData);
    WriteFile(carHeader, BlueData, "output/part8_b.tga");

    Header comparisonHeader;
    comparisonHeader = ReadHeader("examples/EXAMPLE_part1.tga", comparisonHeader);
    vector<Pixel*> comparisonDataR;
    vector<Pixel*> comparisonDataG;
    vector<Pixel*> comparisonDataB;
    comparisonDataR = ReadPixelData(comparisonHeader,"examples/EXAMPLE_part8_r.tga",comparisonDataR);
    comparisonDataG = ReadPixelData(comparisonHeader,"examples/EXAMPLE_part8_g.tga",comparisonDataG);
    comparisonDataB = ReadPixelData(comparisonHeader,"examples/EXAMPLE_part8_b.tga",comparisonDataB);

    if(comparisonDataR == RedData){
        cout << "Red Data Passed" << endl;
    }
    else{
        cout << "Red Data Failed" << endl;
    }

    if(comparisonDataG == GreenData){
        cout << "Green Data Passed" << endl;
    }
    else{
        cout << "Green Data Failed" << endl;
    }

    if(comparisonDataB == BlueData){
        cout << "Blue Data Passed!" << endl;
    }
    else{
        cout << "Blue Failed!" << endl;
    }

    if(comparisonDataR == RedData && comparisonDataG == GreenData && comparisonDataB == BlueData){
        cout << "Passed!" << endl;
        testPassRate++;
    }
    else{
        cout << "Failed!";
    }
}

void TestNine() {
    cout << "Test #9...... ";

    Header layer_redHeader;
layer_redHeader = ReadHeader("input/layer_red.tga", layer_redHeader);

vector<Pixel*> layer_redData;
layer_redData = ReadPixelData(layer_redHeader, "input/layer_red.tga", layer_redData);

Header layer_greenHeader;
layer_greenHeader = ReadHeader("input/layer_green.tga", layer_greenHeader);

vector<Pixel*> layer_greenData;
layer_greenData = ReadPixelData(layer_greenHeader, "input/layer_green.tga", layer_greenData);

Header layer_blueHeader;
layer_blueHeader = ReadHeader("input/layer_blue.tga", layer_blueHeader);

vector<Pixel*> layer_blueData;
layer_blueData = ReadPixelData(layer_blueHeader, "input/layer_blue.tga", layer_blueData);

vector<Pixel*> finalData;
finalData = Combine(layer_blueData, layer_greenData, layer_redData);

WriteFile(layer_redHeader, finalData, "output/part9.tga");

    Header comparisonHeader;
    comparisonHeader = ReadHeader("examples/EXAMPLE_part9.tga", comparisonHeader);
    vector<Pixel*> comparisonData;
    comparisonData = ReadPixelData(comparisonHeader,"examples/EXAMPLE_part9.tga",comparisonData);

    if(comparisonData == finalData){
        cout << "Passed!" << endl;
        testPassRate++;
    }
    else{
        cout << "Failed!" << endl;
    }
}

void TestTen() {
    cout << "Test #10...... ";

    Header text2Header;
text2Header = ReadHeader("input/text2.tga", text2Header);

vector <Pixel*> text2Data;
text2Data = ReadPixelData(text2Header, "input/text2.tga", text2Data);

vector<Pixel*> finalData;
finalData = Rotate(text2Data);

    WriteFile(text2Header, finalData, "output/part10.tga");

    Header comparisonHeader;
    comparisonHeader = ReadHeader("examples/EXAMPLE_part10.tga", comparisonHeader);
    vector<Pixel*> comparisonData;
    comparisonData = ReadPixelData(comparisonHeader,"examples/EXAMPLE_part10.tga",comparisonData);

    if(comparisonData == finalData){
        cout << "Passed!" << endl;
        testPassRate++;
    }
    else{
        cout << "Failed!" << endl;
    }
}