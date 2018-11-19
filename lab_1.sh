#!/bin/sh

REFS_LIST=$(awk -F\" '
{
  split($2, url, " ")
  split($3, data, " ")
  if (data[1] != "-")
  {
     sum[url[2]] += data[1]
  }
}
END { 
  for(i in sum) { 
    print i, sum[i]
  }
}' log.txt | sort -k 2,2nr | head -10)

TOTAL_COUNT=$(echo "$REFS_LIST" | awk '{total = total + $2} END { print total }')

echo "$REFS_LIST" | awk -v total=$TOTAL_COUNT '
{
  printf("%d. %s - %d - %.2f%%\n", NR, $1, $2, $2/total*100)
}
'