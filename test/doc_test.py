import unittest
import numpy as np

import doc as D

class TestDocumentation(unittest.TestCase):
   
    def skip_signatures(self, lines):
        for i in range(4, len(lines)):
            if lines[i].strip() != '' and not lines[i].startswith(' '):
                return lines[i:]
            
    def assert_blank_lines(self, lines):
        for line in lines:
            self.assertEqual(line.strip(), '')
    
    def note_or_warning(self, s, cmt_type = 'note'):
        uc_cmt_type = cmt_type[0].upper() + cmt_type[1:]
        lines = self.skip_signatures(s.splitlines())
        self.assertEqual(lines[0], f'{uc_cmt_type}:')
        self.assertEqual(lines[1], '')
        self.assertEqual(lines[2], f'.. {cmt_type}::')
        self.assertEqual(lines[3], '')
        self.assertTrue(lines[4].startswith(' '))
        self.assertEqual(lines[4].strip(), f'{uc_cmt_type} - line 1.')
        self.assertTrue(lines[5].startswith(' '))
        self.assertEqual(lines[5].strip(), f'{uc_cmt_type} - line 2.')
        self.assertEqual(lines[6], '')
        self.assertEqual(lines[7], f'After {cmt_type}.')
        self.assert_blank_lines(lines[8:])

    def test_f1(self):
        s = D.f1.__doc__
        lines = s.splitlines()
        self.assertEqual(lines[0], 'Dispatched C++ function(s).')
        self.assertEqual(lines[1], '')
        self.assertEqual(lines[2], '::')
        self.assertEqual(lines[3], '')
        self.assertTrue(lines[4].startswith(' '))
        self.assertEqual(lines[4].strip(), '[1] (x: int)')
        self.assertTrue(lines[5].startswith(' '))
        self.assertEqual(lines[5].strip(), '-> int')
        self.assert_blank_lines(lines[6:])
    
    def test_f2(self):
        s = D.f2.__doc__
        lines = self.skip_signatures(s.splitlines())
        self.assertEqual(lines[0], 'Implicit details - line 1.')
        self.assert_blank_lines(lines[1:])

    def test_f3(self):
        s = D.f3.__doc__
        lines = self.skip_signatures(s.splitlines())
        self.assertEqual(lines[0], 'Implicit details - line 1.')
        self.assertEqual(lines[1], '')
        self.assertEqual(lines[2], 'Implicit details - line 2.')
        self.assert_blank_lines(lines[3:])

    def test_f4(self):
        s = D.f4.__doc__
        lines = self.skip_signatures(s.splitlines())
        self.assertEqual(lines[0], 'Explicit brief - line 1.')
        self.assertEqual(lines[1], 'Explicit brief - line 2.')
        self.assertEqual(lines[2], '')
        self.assertEqual(lines[3], 'Explicit details - line 1.')
        self.assertEqual(lines[4], 'Explicit details - line 2.')
        self.assertEqual(lines[5], '')
        self.assertEqual(lines[6], 'Implicit details - line 1.')
        self.assert_blank_lines(lines[7:])

    def test_f5(self):
        s = D.f5.__doc__
        lines = self.skip_signatures(s.splitlines())
        self.assertEqual(lines[0], 'Inline math: :math:`x = 3.1415`.')
        self.assert_blank_lines(lines[1:])

    def test_f6(self):
        s = D.f6.__doc__
        lines = self.skip_signatures(s.splitlines())
        self.assertEqual(lines[0], 'Multiline math:')
        self.assertEqual(lines[1], '')
        self.assertEqual(lines[2], '.. math::')
        self.assertEqual(lines[3], '')
        self.assertTrue(lines[4].startswith(' '))
        self.assertEqual(lines[4].strip(), r'x = 3.1415 \; .')
        self.assertEqual(lines[5], '')
        self.assertEqual(lines[6], 'After math.')
        self.assert_blank_lines(lines[7:])

    def test_f7(self):
        s = D.f7.__doc__
        lines = self.skip_signatures(s.splitlines())
        self.assertEqual(lines[0], 'Math environment:')
        self.assertEqual(lines[1], '')
        self.assertEqual(lines[2], '.. math::')
        self.assertEqual(lines[3], '')
        self.assertTrue(lines[4].startswith(' '))
        self.assertEqual(lines[4].strip(), r'\begin{eqnarray*}')
        self.assertTrue(lines[5].startswith(' '))
        self.assertEqual(lines[5].strip(), r'x &= 3.1415 \; ,')
        self.assertTrue(lines[6].startswith(' '))
        self.assertEqual(lines[6].strip(), r'y &= 2.7182 \; .')
        self.assertTrue(lines[7].startswith(' '))
        self.assertEqual(lines[7].strip(), r'\end{eqnarray*}')
        self.assertEqual(lines[8], '')
        self.assertEqual(lines[9], 'After math.')
        self.assert_blank_lines(lines[10:])
    
    def test_f8(self):
        s = D.f8.__doc__
        lines = self.skip_signatures(s.splitlines())
        self.assertEqual(lines[0], 'Code block:')
        self.assertEqual(lines[1], '')
        self.assertEqual(lines[2], '::')
        self.assertEqual(lines[3], '')
        self.assertTrue(lines[4].startswith(' '))
        self.assertEqual(lines[4].strip(), '#include <iostream>')
        self.assertTrue(lines[5].startswith(' '))
        self.assertEqual(lines[5].strip(), 'int main() {')
        self.assertTrue(lines[6].startswith(' '))
        self.assertEqual(lines[6].strip(), 'std::cout << "Hello, world!" << std::endl;')
        self.assertTrue(lines[7].startswith(' '))
        self.assertEqual(lines[7].strip(), '}')
        self.assertEqual(lines[8], '')
        self.assertEqual(lines[9], 'After code.')
        self.assert_blank_lines(lines[10:])

    def test_f9(self):
        s = D.f9.__doc__
        self.note_or_warning(s, 'note')

    def test_f10(self):
        s = D.f10.__doc__
        self.note_or_warning(s, 'warning')

    def test_f11(self):
        s = D.f11.__doc__
        lines = self.skip_signatures(s.splitlines())
        self.assertEqual(lines[0], 'Parameters')
        self.assertEqual(lines[1], '----------')
        self.assertEqual(lines[2], 'x')
        self.assertTrue(lines[3].startswith(' '))
        self.assertEqual(lines[3].strip(), 'Parameter - line 1.')
        self.assertTrue(lines[4].startswith(' '))
        self.assertEqual(lines[4].strip(), 'Parameter - line 2.')
        self.assert_blank_lines(lines[5:])
    
    def test_f12(self):
        s = D.f12.__doc__
        lines = self.skip_signatures(s.splitlines())
        self.assertEqual(lines[0], 'Returns')
        self.assertEqual(lines[1], '-------')
        self.assertTrue(lines[2].startswith(' '))
        self.assertEqual(lines[2].strip(), 'Return - line 1.')
        self.assertTrue(lines[3].startswith(' '))
        self.assertEqual(lines[3].strip(), 'Return - line 2.')
        self.assert_blank_lines(lines[4:])

    def test_f13(self):
        s = D.f13.__doc__
        lines = self.skip_signatures(s.splitlines())
        self.assertEqual(lines[0], 'Brief - line 1.')
        self.assertEqual(lines[1], 'Brief - line 2.')
        self.assertEqual(lines[2], '')
        self.assertEqual(lines[3], 'Details - line 1.')
        self.assertEqual(lines[4], 'Details - line 2.')
        self.assertEqual(lines[5], '')
        self.assertEqual(lines[6].strip(), 'Multiline math:')
        self.assertEqual(lines[7], '')
        self.assertEqual(lines[8], '.. math::')
        self.assertEqual(lines[9], '')
        self.assertTrue(lines[10].startswith(' '))
        self.assertEqual(lines[10].strip(), r'x = 3.1415 \; .')
        self.assertEqual(lines[11], '')
        self.assertEqual(lines[12], 'List 1:')
        self.assertEqual(lines[13], '* List 1 - item 1.')
        self.assertEqual(lines[14], '* List 1 - item 2.')
        self.assertEqual(lines[15], '')
        self.assertEqual(lines[16], '  * List 1 - item 2.1.')
        self.assertEqual(lines[17], '')
        self.assertEqual(lines[18], '* List 1 - item 3.')
        self.assertEqual(lines[19], '')
        self.assertEqual(lines[20], 'After list.')
        self.assertEqual(lines[21], '')
        self.assertEqual(lines[22], 'Parameters')
        self.assertEqual(lines[23], '----------')
        self.assertEqual(lines[24], 'x')
        self.assertTrue(lines[25].startswith(' '))
        self.assertEqual(lines[25].strip(), 'Parameter - line 1.')
        self.assertEqual(lines[26], '')
        self.assertEqual(lines[27], 'Returns')
        self.assertEqual(lines[28], '-------')
        self.assertTrue(lines[29].startswith(' '))
        self.assertEqual(lines[29].strip(), 'Return - line 1.')
        self.assert_blank_lines(lines[30:])
        

if __name__ == '__main__':
    unittest.main()
