# Exercício 3

def rgb_to_cmyk(r, g, b):
    # Normalize RGB values to the range [0, 1]
    r, g, b = r / 255.0, g / 255.0, b / 255.0
    
    # Calculate K (Black)
    k = min(1 - r, 1 - g, 1 - b)
    
    # If K is 1, it means the color is black, so C, M, Y are all 0
    if k == 1:
        c = m = y = 0
    else:
        # Calculate C, M, and Y values
        c = (1 - r - k) / (1 - k)
        m = (1 - g - k) / (1 - k)
        y = (1 - b - k) / (1 - k)
    
    # Convert to percentage and return the result
    return round(c * 100), round(m * 100), round(y * 100), round(k * 100)

def main():
    # Get RGB values from the user
    try:
        r = int(input("Enter the Red value (0-255): "))
        g = int(input("Enter the Green value (0-255): "))
        b = int(input("Enter the Blue value (0-255): "))

        # Validate input range
        if not (0 <= r <= 255 and 0 <= g <= 255 and 0 <= b <= 255):
            print("Error: RGB values must be between 0 and 255.")
            return
        
        # Convert RGB to CMYK
        c, m, y, k = rgb_to_cmyk(r, g, b)

        # Display the result
        print(f"RGB({r}, {g}, {b}) converts to CMYK:")
        print(f"C = {c}%, M = {m}%, Y = {y}%, K = {k}%")
    
    except ValueError:
        print("Error: Please enter valid integer values for RGB.")

if __name__ == "__main__":
    main()
