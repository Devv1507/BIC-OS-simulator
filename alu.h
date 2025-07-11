#ifndef ALU_H
#define ALU_H

/**
 * @class ALU (Arithmetic Logic Unit)
 * 
 * It specializes in performing all arithmetic and logical operations delegated by the CPU.
 * This class is an internal component of the CPU and has no state of its own;
 * it simply receives operands and returns a result.
 */
class ALU {
public:
    // Constructor
    ALU() { }

    /**
     * @brief Performs the addition of two integers.
     * @param operand1 The first summand.
     * @param operand2 The second summand.
     * @return The result of the addition.
     */
    int add(int operand1, int operand2) {
        return operand1 + operand2;
    }

    /**
     * @brief Increments a value by one.
     * @param value The value to increment.
     * @return The incremented value.
     */
    int increment(int value) {
        return value + 1;
    }

    /**
     * @brief Decrements a value by one.
     * @param value The value to decrement.
     * @return The decremented value.
     */
    int decrement(int value) {
        return value - 1;
    }
};

#endif // ALU_H