#!/usr/bin/env py -3

import os
import shutil
import subprocess
import argparse
import logging
import configparser
'''

:run_tests
echo ::: 
echo : running Tests of:
echo : %MY_TEST_EXE%
echo :::
call %MY_TEST_EXE% -r junit --out %MY_TEST_RESULTS% --input-file %MY_TEST_SELECTION_FILE%
REM call %MY_TEST_EXE% -r console --input-file %MY_TEST_SELECTION_FILE%

:EOF
REM pause
'''
def main():
    parser = argparse.ArgumentParser();
    parser.add_argument("--log", dest='log_file', default='', action="store",
                        help="log filename, if none given logging is only done on screen");
    parser.add_argument("--test_exe", dest='tst_exe', action="store",
                        help="the executable test file");
    parser.add_argument("--cfg", dest='test_cfg', default='tests/test_all.txt', action="store",
                        help="test configuration file");
    parser.add_argument("--report", dest='tst_report', action="store",
                        help="test report file, if none given output is to the console");

    args = parser.parse_args();

    if (args.log_file != ''):
        logging.basicConfig(filename=args.log_file, level=logging.INFO)
    else:
        logging.basicConfig(level=logging.INFO)

    ''' is a test report file given '''
    if ((args.tst_report == None) or (args.tst_report == '')):
        logging.err9r('No test result report file given (option "--report") - ouput to console')
        exit()
    else:
        report_file = os.path.abspath(args.tst_report);
        basedir = os.path.dirname(report_file)
        if (not os.path.exists(basedir)):
            os.makedirs(basedir)
        f = open(report_file, 'w')
        f.close()
        
    if ((args.test_cfg == None) or (not os.path.exists(args.test_cfg))):
        logging.error('test input configuration not found (option "--cfg"):\n %s', args.test_cfg)
        exit()
        
    ''' test if exe is available '''
    exe_file = os.path.abspath(args.tst_exe)
    if (os.path.exists(exe_file)):
        test_cmd = exe_file + ' ' \
            '-r junit' + ' ' \
            '--out ' + report_file + ' ' \
            '--input-file ' + os.path.abspath(args.test_cfg)
        try:
            logging.info("running test cmd:\n %s", test_cmd)
            subprocess.check_output(test_cmd)
        except subprocess.CalledProcessError as e:
            logging.error("test command.\n %s \nreturned:\n %s ", e.cmd, e.output)
            exit()
    else:
        logging.error("test executable not found:\n %s", args.txt_exe)
        exit()
        
    
if __name__ == "__main__":
    main()