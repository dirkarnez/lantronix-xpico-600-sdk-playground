#!/usr/bin/env python3
 
import re
import sys
import argparse
 
def extract_array(content, array_name=None):
    if array_name:
        # Match specific array
        pattern = rf'{array_name}\s*\[\]\s*=\s*\{{(.*?)\}};'
    else:
        # Match first unsigned char array
        pattern = r'unsigned\s+char\s+\w+\s*\[\]\s*=\s*\{(.*?)\};'
 
    match = re.search(pattern, content, re.S)
    if not match:
        raise ValueError("Array not found")
 
    array_body = match.group(1)
 
    # Extract all hex values
    hex_vals = re.findall(r'0x[0-9a-fA-F]+', array_body)
 
    return bytes(int(x, 16) for x in hex_vals)
 
 
def main():
    parser = argparse.ArgumentParser(description="Convert C byte array to binary")
    parser.add_argument("input", help="Input .c file")
    parser.add_argument("output", help="Output .bin file")
    parser.add_argument("--name", help="Array name (optional)", default=None)
 
    args = parser.parse_args()
 
    with open(args.input, "r") as f:
        content = f.read()
 
    data = extract_array(content, args.name)
 
    with open(args.output, "wb") as f:
        f.write(data)
 
    print(f"Written {len(data)} bytes to {args.output}")
 
 
if __name__ == "__main__":
    main()
