# Permutations With Repitition

012 pick 2

  00
  01
  02
  10
  11
  12
  20
  21
  22

```c++

typename t: target const_iterator
typename s: vector<t> reverse_iterator

result = vector<vector<t>>

sample = 0t 0t                 | TYPE vector<t>
        (1s 0s)

s_rbegin = sample.rbegin()     | TYPE s // beginning sample iterator
s_rend   = sample.rend()       | TYPE s // end of sample iterator
scur     = s_rbegin            | TYPE s // current sample iterator
tlim     = prev(target.cend()) | TYPE t // last value of target iterator before end
t_cbegin = target.cbegin()     | TYPE t // last value of target iterator before end

 0t 0t  <-- sample
(1s 0s) <-- sample iterator
    ^ <---- scur

-- while (true) --

 0t 0t
(1s 0s)
    ^

result.push(sample)

if (*scur != tlim)
  ++*scur

---

 0t 1t
(1s 0s)
    ^

result.push(sample)

if (*scur != tlim)
  ++*scur

---

 0t 2t
(1s 0s)
    ^

result.push(sample)

if (*scur == tlim)


  while (*scur == tlim)
    ++scur

   0t 2t
  (1s 0s)
   ^
  
  ++*scur

  while (scur != s_rbegin) {
    --scur
    *scur = t_cbegin
  }

---

 1t 0t
(1s 0s)
    ^

result.push(sample)

if (*scur != tlim)
  ++*scur

---

 1t 1t
(1s 0s)
    ^

result.push(sample)

if (*scur != tlim)
  ++*scur

---

 1t 2t
(1s 0s)
    ^

result.push(sample)

if (*scur == tlim)

  while (*scur == tlim)
    ++scur

   1t 2t
  (1s 0s)
   ^
  
  ++*scur

  while (scur != s_rbegin) {
    --scur
    *scur = t_cbegin
  }

---

 2t 0t
(1s 0s)
    ^

result.push(sample)

if (*scur != tlim)
  ++*scur

---

 2t 1t
(1s 0s)
    ^

result.push(sample)

if (*scur != tlim)
  ++*scur

---

 2t 2t
(1s 0s)
    ^

result.push(sample)

if (*scur == tlim)

  *scur = s_rbegin

  while (*scur == tlim)
    ++scur
    if (scur == s_rend)
      return result

```

__Notes licensed under GNU GPL 3 or later by Justin Collier__
