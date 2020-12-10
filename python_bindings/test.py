import trees

st = trees.SplayTreeInt()
for i in range(1,100,25):
    st.insert(i)
print(st.search(1))
st.printData()

st2 = trees.AVLTreeInt()
for i in range(1,100,25):
    st2.insert(i)
print(st2.search(10))
st2.printData()