import unittest
import numpy as np
from synth_init import Params, ParamsNdc, ANdc

class TestIterable(unittest.TestCase):

   def test_call(self):

        p = ParamsNdc(i=10, v= [1,2,3], ndc1 = ANdc(12))
        d = vars(p)
        self.assertTrue(isinstance(d, dict))
        d['v'] = list(d['v'])
        d['w'] = list(d['w'])
        self.assertEqual(d,  {'i': 10, 'x': 10.0, 'v': [1, 2, 3], 'w': [1, 2, 3], 'ndc1': ANdc(12), 'ndc2': ANdc(9)})

   def test_error(self):
        self.assertRaises(RuntimeError,  lambda : Params() )                           # mandatory param missing
        self.assertRaises(RuntimeError,  lambda : Params(i=10, v= [1,2,3], zzz = 29) ) # Unknown param
        self.assertRaises(RuntimeError,  lambda : Params(i=10, v= 89) )                # Wrong type
        self.assertRaises(RuntimeError,  lambda : Params(10))                          # Positional arguments are not allowed


   def test_call2(self):

        p = Params(i=10, v= [1,2,3], w = [1])

        d = vars(p)
        self.assertTrue(isinstance(d, dict))
        d['v'] = list(d['v'])
        d['w'] = list(d['w'])
        self.assertEqual(d,  {'i': 10, 'x': 10.0, 'v': [1, 2, 3], 'w': [1]})


if __name__ == '__main__':
    unittest.main()


