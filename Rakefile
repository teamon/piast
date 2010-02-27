require "rake/clean"

DEVICE      = "atmega128"
CLOCK       = 8_000_000
PROGRAMMER  = "-c stk500v2 -P avrdoper"
FUSES       = "-U hfuse:w:0xd9:m -U lfuse:w:0x24:m"
CC          = "avr-g++ -Wall -Os -DF_CPU=#{CLOCK} -mmcu=#{DEVICE}"
AVRDUDE     = "avrdude #{PROGRAMMER} -p #{DEVICE}"


CLEAN.include("out/*.o", "out/*.elf", "out/*.hex")
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

