#!/bin/bash

echo -e "\e[34mRunning make...\e[0m"
make > /dev/null
echo -e "\e[32mMake is finished\e[0m"

cat <<EOF > map.ber
11111111111
100P000C111
10000000011
100C00E0001
10000000001
11111111111
EOF

./so_long map.ber

cat <<EOF > map.ber
111
1E1
1P1
111
EOF

./so_long map.ber

cat <<EOF > map.ber
1111
1EP1
1111
EOF

./so_long map.ber

cat <<EOF > map.ber
11101111
1E000P11
11111111
EOF

echo -e "\e[31mFollowing test should return Error\e[0m"
./so_long map.ber

cat <<EOF > map.ber
111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
1E00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000P1
111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
EOF

./so_long map.ber

cat <<EOF > map.ber
11111111111111111
1P000CCC00000E001
10000000000000001
11111111000000001
1C000C11000000001
11111111111111111
EOF

echo -e "\e[31mFollowing test should return Error\e[0m"
./so_long map.ber

cat <<EOF > map.ber
1111111111111111111
1P00000000S000000E1
1CC0000000000111111
1111111111111111111
EOF

echo -e "\e[31mFollowing test should return Error\e[0m"
./so_long map.ber

cat <<EOF > map.ber
1
EOF

echo -e "\e[31mFollowing test should return Error\e[0m"
./so_long map.ber

echo -e "\e[31mFollowing test should return Error\e[0m"
./so_long


echo -e "\e[31mFollowing test should return Error\e[0m"
./so_long blabla.ber

cat <<EOF > map
11111111111
100P000C111
10000000011
100C00E0001
10000000001
11111111111
EOF

echo -e "\e[31mFollowing test should return Error\e[0m"
./so_long map

cat <<EOF > map2.ber
11111111111
100P000C111
10000000011
100C00E0001
10000000001
11111111111
EOF

chmod 000 map2.ber
echo -e "\e[31mFollowing test should return Error\e[0m"
./so_long map2.ber


echo -e "\e[34mRunning make fclean and removing other test files...\e[0m"
rm -f map.ber > /dev/null
rm -f map > /dev/null
rm -f map2.ber > /dev/null
make fclean > /dev/null
echo -e "\e[32mTester is finished\e[0m"
