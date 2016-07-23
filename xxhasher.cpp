#include <xxhash.h>
#include <stdlib.h>
#include <cstdint>
#include <iostream>
#include "args.hxx"

int main(int argc, char **argv)
{
    std::uint64_t seed = 0;
    std::uint32_t bits = 32;

    args::ArgumentParser parser("XXHasher", "A program to generate an XXHASH digest of a simple string");
    args::ValueFlag<int> bits_flag(parser, "bits", "bit depth to use for XXHash algorithm (default 32)", {'b', "bits"});
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    args::ValueFlag<int> seed_flag(parser, "seed", "starting seed to use (default 0)", {'s', "seed"});
    args::Flag verbose(parser, "verbose", "Whether to enter verbose mode", {'v', "verbose"});
    args::Positional<std::string> input_pos(parser, "input", "The input to be hashed");
    try {
        parser.ParseCLI(argc, const_cast<const char **>(argv));
    }
    catch (args::Help) {
        std::cout << parser;
        return 0;
    }
    catch (args::ParseError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    catch (args::ValidationError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    if (bits_flag) {
        bits = args::get(bits_flag);
    }
    if (seed_flag) {
        seed = args::get(seed_flag);
    }
    std::string hash_str;
    if (input_pos) {
        hash_str = args::get(input_pos);
    }
    if (!hash_str.size()) {
        std::cerr << "Input must have nonzero length" << std::endl;
        std::exit(1);
    }
    if (verbose) {
        std::cout << "Input: " << hash_str << std::endl;
        std::cout << "Input length: " << hash_str.size() << std::endl;
        std::cout << "Bit depth: " << bits << std::endl;
        std::cout << "Seed: " << seed << std::endl;
    }

    if (bits == 32) {
        std::cout << XXH32(hash_str.c_str(), hash_str.size(), (std::uint32_t) seed) << std::endl;
    }
    else if (bits == 64) {
        std::cout << XXH64(hash_str.c_str(), hash_str.size(), (std::uint64_t) seed) << std::endl;
    }
    else {
        std::cerr << "Only 32 and 64 bit hashes are supported" << std::endl;
        std::exit(1);
    }
}
