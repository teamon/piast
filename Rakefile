require "rake/clean"

$gen_makefile = false
$makefile_data = ""

def sh(args)
  if $gen_makefile
    $makefile_data << "\t#{args}\n"
  else
    super(args)
  end
end

DEVICE      = "atmega128"
CLOCK       = 8_000_000
PROGRAMMER  = "-c stk500v2 -P avrdoper"
CC          = "avr-g++ -Wall -Os -DF_CPU=#{CLOCK} -mmcu=#{DEVICE}"
AVRDUDE     = "avrdude #{PROGRAMMER} -p #{DEVICE}"


CLEAN.include("out/*.o", "out/*.elf")
OBJ = ["main.o", "buffer.o"]

task :default => [:clean, :build, :flash]

task :build => ["main.hex"]

task :flash do
  sh "#{AVRDUDE} -U flash:w:main.hex:i"	
end

rule /out\/.*\.o/ => proc {|t| t.pathmap('src/%n.cpp')} do |t|
  sh "#{CC} -o #{t.name} -c #{t.source}"
end

file "main.hex" => ["out/main.elf"] do
  sh "avr-objcopy -j .text -j .data -O ihex out/main.elf main.hex"
end

file "out/main.elf" => OBJ.map{|e| "out/#{e}"} do
  sh "#{CC} -o out/main.elf #{OBJ.map{|e| "out/#{e}"}.join(" ")}"
end

desc "Generates a Makefile to build the example code"
task :makefile do
  $gen_makefile = true
  $makefile_data << "all: main\n"
  
  $makefile_data << "main:\n"
  Rake::Task['default'].invoke
  
  $makefile_data << "clean:\n"
  CLEAN.each do |f|
    $makefile_data << "\trm -rf #{f}\n"
  end
  
  $makefile_data << "clobber:\n"
  CLEAN.each do |f|
    $makefile_data << "\trm -rf #{f}\n"
  end
  CLOBBER.each do |f|
    $makefile_data << "\trm -rf #{f}\n"
  end
  
  File.open('Makefile', 'w') { |f| f.write $makefile_data}
end