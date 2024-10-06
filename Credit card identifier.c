#include <stdio.h>

int luhnCheck(long long card_number);
int getCardType(long long card_number);

int main() {
    long long card_number;
    
    // Prompt user for credit card number
    printf("Enter credit card number: ");
    scanf("%lld", &card_number);
    
    // Validate using Luhn's algorithm
    if (luhnCheck(card_number)) {
        // Check the card type if Luhn's validation passes
        int card_type = getCardType(card_number);
        if (card_type == 1) {
            printf("AMEX\n");
        } else if (card_type == 2) {
            printf("MASTERCARD\n");
        } else if (card_type == 3) {
            printf("VISA\n");
        } else {
            printf("INVALID\n");
        }
    } else {
        printf("INVALID\n");
    }
    
    return 0;
}

// Function to validate card number using Luhn's Algorithm
int luhnCheck(long long card_number) {
    int sum = 0;
    int digit_count = 0;
    
    while (card_number > 0) {
        int current_digit = card_number % 10;  // Get the last digit
        card_number /= 10;                      // Remove the last digit
        digit_count++;
        
        // If it's an even position from the right (1-indexed)
        if (digit_count % 2 == 0) {
            int double_digit = current_digit * 2;
            sum += (double_digit > 9) ? (double_digit - 9) : double_digit;  // Add digits of the product
        } else {
            sum += current_digit;  // Odd position digits
        }
    }
    
    return (sum % 10 == 0);  // Valid if sum modulo 10 is 0
}

// Function to identify card type
int getCardType(long long card_number) {
    int length = 0;
    long long temp = card_number;  // Temporary variable to extract digits
    long long first_two_digits = 0;
    
    // Count the length and get the first two digits
    while (temp > 0) {
        if (temp < 100) {
            first_two_digits = temp;  // Last two digits stored here
        }
        temp /= 10;
        length++;
    }
    
    // If the first two digits are more than 0, update them correctly
    if (length > 1) {
        first_two_digits = card_number / (long long)pow(10, length - 2);
    } else {
        first_two_digits = card_number;  // Single digit case
    }

    // Check for American Express (15 digits, starts with 34 or 37)
    if (length == 15 && (first_two_digits == 34 || first_two_digits == 37)) {
        return 1;
    }
    
    // Check for MasterCard (16 digits, starts with 51-55)
    if (length == 16 && (first_two_digits >= 51 && first_two_digits <= 55)) {
        return 2;
    }
    
    // Check for Visa (13 or 16 digits, starts with 4)
    if ((length == 13 || length == 16) && (card_number / (long long)pow(10, length - 1)) == 4) {
        return 3;
    }
    
    // If no match, return INVALID
    return 0;
}
