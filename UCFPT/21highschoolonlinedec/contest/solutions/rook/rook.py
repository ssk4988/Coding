# Python code to insert a node in AVL tree
 
# Generic tree node class
class TreeNode(object):
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.height = 1
 
# AVL tree class which supports the
# Insert operation
class AVL_Tree(object):
 
    # Recursive function to insert key in
    # subtree rooted with node and returns
    # new root of subtree.
    def insert(self, root, key):
     
        # Step 1 - Perform normal BST
        if not root:
            return TreeNode(key)
        elif key < root.val:
            root.left = self.insert(root.left, key)
        else:
            root.right = self.insert(root.right, key)
 
        # Step 2 - Update the height of the
        # ancestor node
        root.height = 1 + max(self.getHeight(root.left),
                           self.getHeight(root.right))
 
        # Step 3 - Get the balance factor
        balance = self.getBalance(root)
 
        # Step 4 - If the node is unbalanced,
        # then try out the 4 cases
        # Case 1 - Left Left
        if balance > 1 and key < root.left.val:
            return self.rightRotate(root)
 
        # Case 2 - Right Right
        if balance < -1 and key > root.right.val:
            return self.leftRotate(root)
 
        # Case 3 - Left Right
        if balance > 1 and key > root.left.val:
            root.left = self.leftRotate(root.left)
            return self.rightRotate(root)
 
        # Case 4 - Right Left
        if balance < -1 and key < root.right.val:
            root.right = self.rightRotate(root.right)
            return self.leftRotate(root)
 
        return root

    # Recursive function to delete a node with
    # given key from subtree with given root.
    # It returns root of the modified subtree.
    def delete(self, root, key):
 
        # Step 1 - Perform standard BST delete
        if not root:
            return root
 
        elif key < root.val:
            root.left = self.delete(root.left, key)
 
        elif key > root.val:
            root.right = self.delete(root.right, key)
 
        else:
            if root.left is None:
                temp = root.right
                root = None
                return temp
 
            elif root.right is None:
                temp = root.left
                root = None
                return temp
 
            temp = self.getMinValueNode(root.right)
            root.val = temp.val
            root.right = self.delete(root.right,
                                      temp.val)
 
        # If the tree has only one node,
        # simply return it
        if root is None:
            return root
 
        # Step 2 - Update the height of the
        # ancestor node
        root.height = 1 + max(self.getHeight(root.left),
                            self.getHeight(root.right))
 
        # Step 3 - Get the balance factor
        balance = self.getBalance(root)
 
        # Step 4 - If the node is unbalanced,
        # then try out the 4 cases
        # Case 1 - Left Left
        if balance > 1 and self.getBalance(root.left) >= 0:
            return self.rightRotate(root)
 
        # Case 2 - Right Right
        if balance < -1 and self.getBalance(root.right) <= 0:
            return self.leftRotate(root)
 
        # Case 3 - Left Right
        if balance > 1 and self.getBalance(root.left) < 0:
            root.left = self.leftRotate(root.left)
            return self.rightRotate(root)
 
        # Case 4 - Right Left
        if balance < -1 and self.getBalance(root.right) > 0:
            root.right = self.rightRotate(root.right)
            return self.leftRotate(root)
 
        return root

    def lower(self, root, key):
        if root is None:
            return None
        if root.val < key:
            right = self.lower(root.right, key)
            if right is None:
                return root.val
            return right
        else:
            return self.lower(root.left, key)

    def higher(self, root, key):
        if root is None:
            return None
        if root.val > key:
            left = self.higher(root.left, key)
            if left is None:
                return root.val
            return left
        else:
            return self.higher(root.right, key)
 
    def leftRotate(self, z):
 
        y = z.right
        T2 = y.left
 
        # Perform rotation
        y.left = z
        z.right = T2
 
        # Update heights
        z.height = 1 + max(self.getHeight(z.left),
                         self.getHeight(z.right))
        y.height = 1 + max(self.getHeight(y.left),
                         self.getHeight(y.right))
 
        # Return the new root
        return y
 
    def rightRotate(self, z):
 
        y = z.left
        T3 = y.right
 
        # Perform rotation
        y.right = z
        z.left = T3
 
        # Update heights
        z.height = 1 + max(self.getHeight(z.left),
                        self.getHeight(z.right))
        y.height = 1 + max(self.getHeight(y.left),
                        self.getHeight(y.right))
 
        # Return the new root
        return y
 
    def getHeight(self, root):
        if not root:
            return 0
 
        return root.height
 
    def getBalance(self, root):
        if not root:
            return 0
 
        return self.getHeight(root.left) - self.getHeight(root.right)

    def getMinValueNode(self, root):
        if root is None or root.left is None:
            return root
 
        return self.getMinValueNode(root.left)

    def preOrder(self, root):
 
        if not root:
            return
 
        print("{0} ".format(root.val), end="")
        self.preOrder(root.left)
        self.preOrder(root.right)
 
num_tests = int(input())

for q in range(num_tests):
    n = int(input())
    inp = input().split(" ")
    rook_pos = int(inp[0])

    pawns_curr = AVL_Tree()
    root_curr = None
    pawns_above = AVL_Tree()
    root_above = None
    mapper = {}

    for i in range(n):
        x = int(inp[i+1])
        root_curr = pawns_curr.insert(root_curr, x)
        mapper[x] = i+1

    active_pawns = n
    turn = 0

    result = []

    while active_pawns > 1:
        if turn == 0:
            left_pawn = pawns_curr.lower(root_curr, rook_pos)
            right_pawn = pawns_curr.higher(root_curr, rook_pos)

            if left_pawn is None and right_pawn is None:
                pawns_curr = pawns_above
                root_curr = root_above
                pawns_above = AVL_Tree()
                root_above = None
            else:
                dist_left = rook_pos-left_pawn if left_pawn is not None else 999999999999999999999
                dist_right = right_pawn-rook_pos if right_pawn is not None else 999999999999999999999

                if dist_left <= dist_right:
                    root_curr = pawns_curr.delete(root_curr, left_pawn)
                    rook_pos = left_pawn
                    result.append(left_pawn)
                else:
                    root_curr = pawns_curr.delete(root_curr, right_pawn)
                    rook_pos = right_pawn
                    result.append(right_pawn)
                
                active_pawns = active_pawns-1
        else:
            left_pawn = pawns_curr.lower(root_curr, rook_pos)
            right_pawn = pawns_curr.higher(root_curr, rook_pos)
            
            if left_pawn is None and right_pawn is None:
                turn = turn ^ 1
                continue

            dist_left = rook_pos-left_pawn if left_pawn is not None else 999999999999999999999
            dist_right = right_pawn-rook_pos if right_pawn is not None else 999999999999999999999

            if dist_left <= dist_right:
                root_curr = pawns_curr.delete(root_curr, left_pawn)
                root_above = pawns_above.insert(root_above, left_pawn)
            else:
                root_curr = pawns_curr.delete(root_curr, right_pawn)
                root_above = pawns_above.insert(root_above, right_pawn)

        turn = turn ^ 1
    
    for i in range(len(result)):
        if i > 0:
            print(" ",end='')
        print(mapper[result[i]],end='')
    print()
