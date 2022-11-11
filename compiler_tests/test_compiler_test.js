// todo;

import { execSync } from 'node:child_process';
import * as fs from 'node:fs';

let q = ''
let print = console.log

q += JSON.stringify(process.argv, null, 4)
print('------------------------------------------------------')
print('testing ', process.argv[3], ' of ', process.argv[2])

//process.exit(-1)
// pass the compiler in here please - well,

let exitCode = 0

try {
    // tbh probably do this in a folder of its own
    //execSync('riscv64-unknown-elf-gcc -Ofast -march=rv32imafd -mabi=ilp32d -c broken.c',
    execSync('clang++ -std=c++14 -fsyntax-only ' + argv[2],// 'main.cpp',
        (error, stdout, stderr) => {
            if (process.argv[2] === 'fail') {
                exitCode = 1;
            }

            // console.log('WJAT?')
//            console.log('ERROR [', error, ']')
//            console.log(stdout)
//            console.log(stderr)
//            process.exit(0)
        })
} catch (e) {
    // compilation failed
    if (process.argv[2] === 'pass') {
        exitCode = 1;
    }

    //console.log('EXCEPTION', e)
                // more than likely the exit code was not 0
                // in which case you're here
                // the exception has pretty much everything in it
//    console.log('EXCEPTION')
    // success! You wanted to fail right???!!
//    process.exit(0)
}

fs.writeFileSync('' + Date.now() + '.txt', q)

process.exit(exitCode)
