def args
	string = ''

	$variables.each_with_index do |var, index|
		string = string + var.tr('@', ' ')
		string = string + ', ' if (index + 1) < $variables.count
	end
	return string
end

def constructor
	$variables.each do |var|
		$output.puts("\tthis->_#{var.split('@').last} = #{var.split('@').last}")
	end
end

def copy_constructor
	$variables.each do |var|
		$output.puts("\tthis->_#{var.split('@').last} = obj.#{var.split('@').last}")
	end
end

def equals_operator
	$variables.each do |var|
		$output.puts("\tthis->_#{var.split('@').last} = obj.#{var.split('@').last}")
	end
end

$classname = ARGV[0].capitalize
$variables = []

iterator = 1
loop do
	break if ARGV[iterator].nil?
	$variables << ARGV[iterator]
	iterator += 1
end

puts "Generating #{$classname}.cpp and #{$classname}.hpp"

$template = File.open('TC.cpp')
$output = File.open("#{$classname}.cpp", 'w')

$template.each do |line|
	$output.puts(line.gsub(/<args>/, args).gsub(/<classname>/, $classname))  and next if line.match(/<args>/)
	constructor                                                              and next if line.match(/<constructor>/)
	copy_constructor                                                         and next if line.match(/<copy constructor>/)
	equals_operator                                                          and next if line.match(/<= operator>/)

	$output.puts(line.gsub(/<classname>/, $classname))
end

