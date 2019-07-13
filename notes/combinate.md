# Combinations

012345 pick 4

  0123
  0124
  0125
  0134
  0135
  0145
  0234
  0235
  0245
  0345
  1234
  1235
  1245
  1345
  2345

```c++

typename t: target const_iterator
typename s: vector<t> reverse_iterator

result = vector<vector<t>>

sample = 0t 1t 2t 3t           | TYPE vector<t>
        (3s 2s 1s 0s)

s_rbegin = sample.rbegin()     | TYPE s // beginning sample iterator
s_rend   = sample.rend()       | TYPE s // end of sample iterator
scur     = s_rbegin            | TYPE s // current sample iterator
tlim     = prev(target.cend()) | TYPE t // last value of target iterator before end

 0t 1t 2t 3t  <-- sample
(3s 2s 1s 0s) <-- sample iterator
(2t 3t 4t 5t) <-- tlim
          ^ <---- scur

-- while (true) --

 0t 1t 2t 3t
(3s 2s 1s 0s)
(2t 3t 4t 5t)
          ^

result.push(sample)

if (*scur != tlim)
  ++*scur

---

 0t 1t 2t 4t
(3s 2s 1s 0s)
(2t 3t 4t 5t)
          ^

result.push(sample)

if (*scur != tlim)
  ++*scur

---

 0t 1t 2t 5t
(3s 2s 1s 0s)
(2t 3t 4t 5t)
          ^

result.push(sample)

if (*scur == tlim)
  while (*scur == tlim)
    ++scur
    --tlim

   0t 1t 2t 5t
  (3s 2s 1s 0s)
  (2t 3t 4t 5t)
         ^
  
  tnext = next(*scur) // 3t
  while (*scur != tnext)
    *scur = tnext
    if (scur != s_rbegin)
      --scur
      ++tlim
      ++tnext

---

 0t 1t 3t 4t
(3s 2s 1s 0s)
(2t 3t 4t 5t)
          ^

result.push(sample)

if (*scur != tlim)
  ++*scur

---

 0t 1t 3t 5t
(3s 2s 1s 0s)
(2t 3t 4t 5t)
          ^

result.push(sample)

if (*scur == tlim)
  while (*scur == tlim)
    ++scur
    --tlim

   0t 1t 3t 5t
  (3s 2s 1s 0s)
  (2t 3t 4t 5t)
         ^

  tnext = next(*scur) // 4t
  while (*scur != tnext)
    *scur = tnext
    if (scur != s_rbegin)
      --scur
      ++tlim
      ++tnext

---

 0t 1t 4t 5t
(3s 2s 1s 0s)
(2t 3t 4t 5t)
          ^

result.push(sample)

if (*scur == tlim)
  while (*scur == tlim)
    ++scur
    --tlim

   0t 1t 4t 5t
  (3s 2s 1s 0s)
  (2t 3t 4t 5t)
      ^

  tnext = next(*scur) // 2t
  while (*scur != tnext)
    *scur = tnext
    if (scur != s_rbegin)
      --scur
      ++tlim
      ++tnext

---

 0t 2t 3t 4t
(3s 2s 1s 0s)
(2t 3t 4t 5t)
          ^

result.push(sample)

if (*scur != tlim)
  ++*scur

---

 0t 2t 3t 5t
(3s 2s 1s 0s)
(2t 3t 4t 5t)
          ^

result.push(sample)

if (*scur == tlim)
  while (*scur == tlim)
    ++scur
    --tlim

   0t 2t 3t 5t
  (3s 2s 1s 0s)
  (2t 3t 4t 5t)
         ^

  tnext = next(*scur) // 4t
  while (*scur != tnext)
    *scur = tnext
    if (scur != s_rbegin)
      --scur
      ++tlim
      ++tnext

---

 0t 2t 4t 5t
(3s 2s 1s 0s)
(2t 3t 4t 5t)
          ^

result.push(sample)

if (*scur == tlim)
  while (*scur == tlim)
    ++scur
    --tlim

   0t 2t 4t 5t
  (3s 2s 1s 0s)
  (2t 3t 4t 5t)
      ^

  tnext = next(*scur) // 3t
  while (*scur != tnext)
    *scur = tnext
    if (scur != s_rbegin)
      --scur
      ++tlim
      ++tnext

---

 0t 3t 4t 5t
(3s 2s 1s 0s)
(2t 3t 4t 5t)
       ^

result.push(sample)

if (*scur == tlim)
  while (*scur == tlim)
    ++scur
    --tlim

   0t 3t 4t 5t
  (3s 2s 1s 0s)
  (2t 3t 4t 5t)
   ^

  tnext = next(*scur) // 1t
  while (*scur != tnext)
    *scur = tnext
    if (scur != s_rbegin)
      --scur
      ++tlim
      ++tnext

---

 1t 2t 3t 4t
(3s 2s 1s 0s)
(2t 3t 4t 5t)
          ^

result.push(sample)

if (*scur != tlim)
  ++*scur

---

 1t 2t 3t 5t
(3s 2s 1s 0s)
(2t 3t 4t 5t)
          ^

result.push(sample)

if (*scur == tlim)
  while (*scur == tlim)
    ++scur
    --tlim

   1t 2t 3t 5t
  (3s 2s 1s 0s)
  (2t 3t 4t 5t)
         ^

  tnext = next(*scur) // 4t
  while (*scur != tnext)
    *scur = tnext
    if (scur != s_rbegin)
      --scur
      ++tlim
      ++tnext

---

 1t 2t 4t 5t
(3s 2s 1s 0s)
(2t 3t 4t 5t)
          ^

result.push(sample)

if (*scur == tlim)
  while (*scur == tlim)
    ++scur
    --tlim

   1t 2t 4t 5t
  (3s 2s 1s 0s)
  (2t 3t 4t 5t)
      ^

  tnext = next(*scur) // 3t
  while (*scur != tnext)
    *scur = tnext
    if (scur != s_rbegin)
      --scur
      ++tlim
      ++tnext

---

 1t 3t 4t 5t
(3s 2s 1s 0s)
(2t 3t 4t 5t)
       ^

result.push(sample)

if (*scur == tlim)
  while (*scur == tlim)
    ++scur
    --tlim

   1t 3t 4t 5t
  (3s 2s 1s 0s)
  (2t 3t 4t 5t)
   ^

  tnext = next(*scur) // 2t
  while (*scur != tnext)
    *scur = tnext
    if (scur != s_rbegin)
      --scur
      ++tlim
      ++tnext

---

 2t 3t 4t 5t
(3s 2s 1s 0s)
(2t 3t 4t 5t)
    ^

result.push(sample)

if (*scur == tlim)
  while (*scur == tlim)
    ++scur
    --tlim
    if (scur == s_rend)
      return

```

__Notes licensed under GNU GPL 3 or later by Justin Collier__
