/* References:
   - https://github.com/dystopiancode/pcm-g711/tree/master
   - https://en.wikipedia.org/wiki/G.711
   - https://dystopiancode.blogspot.com/2012/02/pcm-law-and-u-law-companding-algorithms.html
*/

// Include necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Define constants used for μ-law encoding and decoding
#define SIGN_BIT    (0x80)    // Sign bit for μ-law byte, used for encoding
#define QUANT_MASK  (0x0F)    // Mask to extract the quantization bits
#define SEG_SHIFT   (4)       // Number of bits to left shift for segment number
#define BIAS        (0x84)    // Bias for linear code
#define SEG_MASK    (0x70)    // Mask to extract the segment number
#define CLIP        32635     // Clipping value for the magnitude of the signal

/**
 * Function: MuLawToLinearPCM
 * --------------------------
 * Converts a μ-law encoded byte to a 16-bit linear PCM value.
 *
 * Parameters:
 *   muLawValue - The μ-law encoded byte to be converted.
 *
 * Returns:
 *   A 16-bit linear PCM value.
 */
short MuLawToLinearPCM(unsigned char muLawValue) {
    short t;
    muLawValue = ~muLawValue;  // Complement the μ-law value to get the original signal value
    t = ((muLawValue & QUANT_MASK) << 3) + BIAS;  // Extract and scale the quantization bits
    t <<= ((unsigned)muLawValue & SEG_MASK) >> SEG_SHIFT;  // Shift the value based on the segment
    return ((muLawValue & SIGN_BIT) ? (BIAS - t) : (t - BIAS));  // Return the final PCM value
}

// Define a standard header for the μ-law WAV format
uint8_t wavHeader[] = {
    // 'RIFF' chunk descriptor
    'R', 'I', 'F', 'F',           // ChunkID
    0x00, 0x00, 0x00, 0x00,       // ChunkSize (placeholder, will be updated later)
    'W', 'A', 'V', 'E',           // Format

    // 'fmt ' sub-chunk (format information)
    'f', 'm', 't', ' ',           // Subchunk1ID
    0x10, 0x00, 0x00, 0x00,       // Subchunk1Size (16 for PCM)
    0x01, 0x00,                   // AudioFormat (PCM)
    0x01, 0x00,                   // NumChannels (1 channel)
    0x40, 0x1F, 0x00, 0x00,       // SampleRate (8000 Hz)
    0x80, 0x3E, 0x00, 0x00,       // ByteRate (SampleRate * NumChannels * BitsPerSample/8)
    0x02, 0x00,                   // BlockAlign (NumChannels * BitsPerSample/8)
    0x10, 0x00,                   // BitsPerSample (16 bits)

    // 'data' sub-chunk (actual sound data)
    'd', 'a', 't', 'a',           // Subchunk2ID
    0x00, 0x00, 0x00, 0x00        // Subchunk2Size (placeholder, will be updated later)
};

/**
 * Function: main
 * --------------
 * Main function that reads μ-law encoded audio data from an input file,
 * converts it to linear PCM, and writes the decoded data to an output file.
 *
 * Returns:
 *   An integer indicating the success (0) or failure (1) of the program.
 */
int main() {
    // Specify the paths to the input and output files
    const char* inputFilePath = "Au8A_eng_f2.wav";
    const char* outputFilePath = "decoded_output.wav";

    // Open the input file for reading
    FILE *inputFile = fopen(inputFilePath, "rb");
    if (inputFile == NULL) {
        fprintf(stderr, "Could not open input file %s\n", inputFilePath);
        return 1;
    }

    // Open the output file for writing
    FILE *outputFile = fopen(outputFilePath, "wb+");
    if (outputFile == NULL) {
        fprintf(stderr, "Could not open output file %s\n", outputFilePath);
        fclose(inputFile);
        return 1;
    }

    // Write the placeholder header to the output file
    fwrite(wavHeader, sizeof(wavHeader), 1, outputFile);

    // Prepare to read and decode the μ-law data
    uint8_t buffer;
    uint16_t pcmOutput;
    size_t dataChunkSize = 0;

    // Skip the header of the input file as it's not needed for decoding
    fseek(inputFile, 44, SEEK_SET);

    // Decode each μ-law byte and write the output as PCM data
    while (fread(&buffer, sizeof(buffer), 1, inputFile) == 1) {
        pcmOutput = MuLawToLinearPCM(buffer);
        fwrite(&pcmOutput, sizeof(pcmOutput), 1, outputFile);
        dataChunkSize += sizeof(pcmOutput);
    }

    // Update the sizes in the header with the actual data size
    uint32_t riffChunkSize = dataChunkSize + 36; // Calculate RIFF chunk size
    fseek(outputFile, 4, SEEK_SET); // Move to the RIFF chunk size position
    fwrite(&riffChunkSize, sizeof(riffChunkSize), 1, outputFile);

    // Move to the 'data' subchunk size position and write it
    fseek(outputFile, 40, SEEK_SET);
    fwrite(&dataChunkSize, sizeof(dataChunkSize), 1, outputFile);

    // Close the input and output files
    fclose(inputFile);
    fclose(outputFile);

    // Indicate successful decoding
    printf("Decoding complete.\n");

    return 0;
}
