
# Exception Handling in Python

# import sys

# class MyException(Exception) :

#     def __init__(this, errorMessege: str) :  this.__errMsz = errorMessege
#     def __str__(this) :  return repr(this.__errMsz)


# try : raise NameError("Name is not Defined")

# except NameError as errMsz : print(errMsz)



from os import environ as temp_env_var_set
temp_env_var_set["TF_CPP_MIN_LOG_LEVEL"] = "1"

# tensorflow test
import tensorflow as tf

print(tf.__version__)

rank_tensor1 = tf.Variable( [1, 2.0, 3.0], float )
rank_tensor2 = tf.Variable([[1, 2], [3, 4], [5, 6]])

print(rank_tensor1)
print(rank_tensor2)
