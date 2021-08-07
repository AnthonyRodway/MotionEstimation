This implementation of the SAD algorithm has the following optimizations:
 * Registers for frequently changed variables
 * Store four pixels (instead of one pixel) in each of the two registers (from reference block and current block)
    * Registers can hold four bytes and a pixel is only one byte, so we can store four pixels in one register
    * With this, we also iterate over every four pixels instead of one
    * We use bitwise operators to minimize the performance impact