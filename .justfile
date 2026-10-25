make:
  gcc -Wall -Wextra -std=c23 -pedantic -Werror -g -I src/ src/*.c -o stackmachine
  chmod +x stackmachine
