import io,subprocess,pathlib
from capstone import Cs,CS_ARCH_ARM,CS_MODE_ARM
from elftools.elf.elffile import ELFFile
ROOT=pathlib.Path('.').resolve()
ST=ROOT.parent/'st'
MWCC=ST/'tools'/'mwccarm'/'1.2'/'sp2p3'/'mwccarm.exe'
FLAGS="-O4,p -enum int -lang c99 -char signed -interworking -proc arm946e -gccext,on -msgstyle gcc".split()
out=pathlib.Path('/tmp/c.o')
subprocess.run(['/opt/homebrew/bin/wine',str(MWCC),*FLAGS,'-c','ai/scratch/agent_02083c18.c','-o',str(out)],cwd=ROOT,capture_output=True)
elf=ELFFile(io.BytesIO(out.read_bytes()))
st=elf.get_section_by_name('.symtab')
sym=next(s for s in st.iter_symbols() if s.name=='func_02083c18')
sec=elf.get_section(sym['st_shndx'])
data=sec.data()[sym['st_value']:sym['st_value']+sym['st_size']]
md=Cs(CS_ARCH_ARM,CS_MODE_ARM)
for ins in md.disasm(data,0x02083c18):
    print(f"{ins.address:08x}  {ins.mnemonic:8} {ins.op_str}")
