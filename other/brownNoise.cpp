#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

int main() {
    const int sampleRate = 44100;
    const int duration = 5;
    const int numSamples = sampleRate * duration;

    vector<float> brownNoise(numSamples);

    default_random_engine generator;
    normal_distribution<float> distribution(0.0f, 0.02f);

    float lastSample = 0.0f;

    for (int i = 0; i < numSamples; ++i) {
        float change = distribution(generator);
        lastSample += change;
        
        if (lastSample > 1.0f) lastSample = 1.0f;
        if (lastSample < -1.0f) lastSample = -1.0f;

        brownNoise[i] = lastSample;
    }

    // write to a raw PCM file (16-bit) - you can open this with Audacity
    ofstream outFile("brownNoise.raw", ios::binary);
    for (float sample : brownNoise) {
        int16_t pcm = static_cast<int16_t>(sample * 32767.0f);
        outFile.write(reinterpret_cast<char*>(&pcm), sizeof(pcm));
    }

    outFile.close();
    cout << "Brown noise generated as 'brown_noise.raw'" << endl;

    return 0;
}
